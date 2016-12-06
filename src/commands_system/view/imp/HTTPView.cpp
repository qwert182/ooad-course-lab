#include "HTTPView.h"


#include <memory.h>
#include <string.h>

#include <string>
#include <map>
#include <fstream>

#include <sstream>
#include <vector>
#include <algorithm>

#include <signal.h>

#include <type_traits>
#include "../../utils/formatTypeidName.h"


#include "../../utils/Exception.h"



class SocketException : public HTTPException {
public:
	SocketException(const char *what) : HTTPException(what) {}
};

class StatusHTTPException : public HTTPException {
	int status;
public:
	int getStatus() const {
		return status;
	}

	StatusHTTPException(const char *what, int status) : HTTPException(what), status(status) {}
};

class BadRequestException : public StatusHTTPException {
public:
	BadRequestException(const char *what) : StatusHTTPException(what, 400) {}
};

class NotFoundException : public StatusHTTPException {
public:
	NotFoundException(const char *what) : StatusHTTPException(what, 404) {}
	NotFoundException(const std::string &what) : StatusHTTPException(what.c_str(), 404) {}
};

class NotImplementedException : public StatusHTTPException {
public:
	NotImplementedException(const char *what) : StatusHTTPException(what, 501) {}
};




using std::string;
using std::map;
using std::make_pair;
using std::ifstream;
using std::istringstream;
using std::vector;
using std::find;
using std::search;



static
map<string, string> init_from_array() {
  map<string, string> m;
	m.insert(make_pair("/", "html/index.htm"));
	m.insert(make_pair("/main.css", "html/main.css"));
	return m;
}






static
SOCKET current_socket;

static
bool has_control_c_pressed = false;

static
void on_control_c_pressed(int) { // shortly double hit ctrl^c causes abort() message
	closesocket(current_socket);
	has_control_c_pressed = true;
}







HTTPView::HTTPView() : path_to_file(init_from_array()) {
  WSADATA wd;
  struct servent const *http;
  union {sockaddr a; sockaddr_in i;} addr;

  void (*prev_signal)(int) = signal(SIGINT, on_control_c_pressed); // may be not thread safe (races)
	if (prev_signal != SIG_DFL)
		throw HTTPException("only one server can exist in one time");


	if (WSAStartup(MAKEWORD(1, 1), &wd))
		throw SocketException("in WSAStartup");

	if ((http = getservbyname("http", "tcp")) == NULL)
		throw SocketException("in getservbyname");

	memset(&addr, 0, sizeof addr);
	addr.i.sin_family = AF_INET;
	addr.i.sin_port = http->s_port;
	addr.i.sin_addr.s_addr = htonl(INADDR_ANY);

	if ((s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET)
		throw SocketException("in socket creation");

	if (bind(s, &addr.a, sizeof addr.a))
		throw SocketException("in bind");
}




HTTPView::~HTTPView() {
	signal(SIGINT, SIG_DFL);

	if (closesocket(s))
		if (!has_control_c_pressed)
			throw SocketException("in closesocket");

	if (WSACleanup())
		throw SocketException("in WSACleanup");
}




static
void recvToVector(SOCKET a, vector<char> &data) {
  int size;
  char buf[4];
	
	if ((size = recv(a, buf, sizeof buf, 0)) < 0)
		throw SocketException("in recv");
	if (size == 0)
		throw SocketException("recv received 0 bytes");

	data.insert(data.end(), buf, &buf[size]);
}





string moveNewDataToString(const vector<char> &data, size_t last_size, const char *barrier) {
  vector<char>::const_iterator
	start = data.begin() + last_size,
	start_search;
  size_t barrier_len = strlen(barrier);
  const char *barrier_end = barrier + barrier_len;

	if (barrier_len + (data.size() - last_size) >= data.size())
		start_search = data.begin();
	else
		start_search = data.end() - barrier_len - (data.size() - last_size);

  vector<char>::const_iterator found_barrier = search(start_search, data.end(), barrier, barrier_end);
  vector<char>::const_iterator found_nullchar = find(start_search, data.end(), '\0');

	if (found_nullchar != data.end() && (found_barrier == data.end() || found_nullchar < found_barrier))
		throw BadRequestException("HTTP header is not a string (contains '\\0')");

	if (found_barrier != data.end())
		found_barrier += barrier_len;

	return string(start, found_barrier);
}

string recvToString(SOCKET a, vector<char> &data) {
  size_t last_size = data.size();
	recvToVector(a, data);
	return moveNewDataToString(data, last_size, "\r\n\r\n");
}


void trim(string &s) {
	static const char spaces[] = " \t";
	size_t start = s.find_first_not_of(spaces);
	s.erase(0, start);
	size_t end = s.find_last_not_of(spaces);
	if (end != string::npos)
		s.erase(end + 1);
}


struct Request {
	string
		type,
		path,
		version,
		all;

	map<string, string>
		headers;

	vector<char>
		content;

	void set_headers(const string &all) {
	  size_t end_pos = all.find("\r\n\r\n");
		if (end_pos == all.npos) return;

	  size_t cur_pos;
	  size_t next_pos = all.find("\r\n");

		while (next_pos != end_pos) {
			cur_pos = next_pos + 2;
			next_pos = all.find("\r\n", cur_pos);
			if (all[next_pos + 2] == ' ')
				throw BadRequestException("LWS is not supported yet");

		  string field_line = all.substr(cur_pos, next_pos - cur_pos);
		  size_t col_pos = field_line.find(':');

			if (col_pos == string::npos)
				throw BadRequestException("message geader must contain \":\"");

		  string field_name = field_line.substr(0, col_pos);
			trim(field_name);

		  string field_value = field_line.substr(col_pos + 1);
			trim(field_value);

			headers.insert(make_pair(field_name, field_value));
		}
	}

	void correct_path() {
	  size_t ss;
		if (path.length() == 0)
			throw BadRequestException("HTTP request must contain Request-URI");
		if ((ss = path.find("://")) != path.npos) {
			size_t s;
			if ((s = path.find('/', ss + 3)) != path.npos) {
				path.erase(0, s);
			} else {
				path = '/';
			}
		}
	}

	void set_09(const string &line, size_t sp) {
		version = "HTTP/0.9";
		path = line.substr(sp + 1);
		correct_path();
	}

	void set_10(const string &all, size_t sp_first, size_t sp_last) {
		version = all.substr(sp_last + 1, all.find('\r') - sp_last - 1);
		path = all.substr(sp_first + 1, sp_last - sp_first - 1);
		correct_path();
		set_headers(all);
	}

	// HTTP 0.9
	Request(const string &line, int version, int sp_first, int sp_last) {
		type = line.substr(0, sp_first);

		if (version == 9  &&  type != "GET")
			throw BadRequestException("HTTP/0.9 request must be GET");

		if (version == 10  &&  type != "GET"  &&  type != "POST")
			throw NotImplementedException("supported only GET and POST");

		if (version == 9) set_09(line, sp_first);
		else if (version == 10) set_10(line, sp_first, sp_last);
		this->all = line;

		if (path.find('/') != 0)
			throw BadRequestException("HTTP request must contain absolute path");
	}
};


static
Request receiveRequest(SOCKET a) {
  string all;
  size_t sp_first, sp_last;
  vector<char> data;

	for (;;) {
		all += recvToString(a, data);

	  size_t r = all.find("\r\n");
		if (r != string::npos) {
		  string line = all.substr(0, r);
			sp_first = line.find_first_of(' ') ;
			sp_last = line.find_last_of(' ');
			if (sp_first == line.npos)
				throw BadRequestException("first line of HTTP request must contain space");
			if (sp_first == sp_last) { // HTTP 0.9
				return Request(line, 9, sp_first, sp_last);
			} else { // HTTP 1.0+
				break;
			}
		}
	}

  size_t end;
	while ((end = all.find("\r\n\r\n")) == all.npos) {
		all += recvToString(a, data);
	}

  Request request = Request(all, 10, sp_first, sp_last);

	if (request.type == "GET") {
		if (end != all.length() - 4)
			throw BadRequestException("receiveHTTPRequest");
	} else if (request.type == "POST") {
	  auto _content_length = request.headers.find("Content-Length");
		if (_content_length == request.headers.end()) throw BadRequestException("Content-Length not found");
	  istringstream convert(_content_length->second);
	  size_t content_length;
		convert >> content_length;
		if (convert.bad() || !convert.eof()) throw BadRequestException("bad Content-Length");


	  vector<char> content(data.begin() + end + strlen("\r\n\r\n"), data.end());
		while (content.size() < content_length) {
			recvToVector(a, content);
		}
		if (content.size() != content_length)
			throw BadRequestException("actual content length != Content-Length");

		request.content = content;
	} else {
		throw NotImplementedException(request.type.c_str());
	}

	return request;
}






void send_file(SOCKET a, const string &filename) {
  char buf[1000];
  int size;
  ifstream f(filename, std::ios::binary);

	if (!f.good())
		throw NotFoundException("can't open file \"" + filename + "\"");

	while ((f.read(buf, sizeof(buf)),  (size = (int)f.gcount()) != 0)) {
		if (send(a, buf, size, 0) != size)
			throw SocketException("in send_file");
	}
}

void send_response(SOCKET a, int code) {
  char buf[100];
  int size;
	size = sprintf(buf, "HTTP/1.0 %d \r\n\r\n", code);
	if (send(a, buf, size, 0) != size)
		throw SocketException("in send_response");
}



#include <iostream>

using std::cout;
using std::endl;


void HTTPView::server() {
  SOCKET a = INVALID_SOCKET;
  union {sockaddr a; sockaddr_in i;} addr;
  int addr_len;


	if (listen(s, 2))
		throw SocketException("can't listen");

	for (;;) {
		try {
			addr_len = sizeof addr.a;
			memset(&addr, 0, sizeof addr.a);

			current_socket = s; // global variable
			if ((a = accept(s, &addr.a, &addr_len)) == INVALID_SOCKET) {
				throw SocketException("in accept");
			}

			cout << "accept" << endl;


			Request request = receiveRequest(a);
			cout << "request\n";
			cout << "\t\"" << request.type << "\"\n";
			cout << "\t\"" << request.path << '\"' << endl;
			cout << '{';
			cout << request.all;
			cout << '}' << endl;

			if (request.type == "GET") {
				auto found = path_to_file.find(request.path);
				if (found != path_to_file.end()) {
					send_response(a, 200);
					send_file(a, found->second);
					cout << "sended\n";
					cout << "\t\"" << found->second << '\"' << endl;
				} else {
					send_response(a, 404);
					cout << "\t" "resource not found" << endl;
				}
			}
		} catch (const SocketException &e) {
			if (has_control_c_pressed) { // global variable
				closesocket(a); a = INVALID_SOCKET;
				break;
			}
			cout << "\t" "SocketException: " << e.what() << endl;
		} catch (const StatusHTTPException &e) {
			cout << "\t" "StatusHTTPException: " << formatTypeidName(typeid(e).name()) << ": \n";
			cout << "\t" "status: " << e.getStatus() << '\n';
			cout << "\t" "what: " << e.what() << endl;

			send_response(a, e.getStatus());
			cout << "sended response" << endl;
		}

		cout << "close\n";
		{
			int res = closesocket(a);
			a = INVALID_SOCKET;
			if (res)
				throw SocketException("in closesocket");
		}
	}
}






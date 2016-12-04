#include "HTTPView.h"


#include <memory.h>
#include <string.h>

#include <string>
#include <map>
#include <fstream>


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




/*
struct Header {
	string
		type,
		path,
		version;
	map<string, string>
		content;
};


static
Header parseHeader(const string &header) {
  size_t r = header.find_first_of('\r');
  size_t f = header.find_first_of(' ');
  size_t l = header.find_last_of(' ', r);
  Header h;
	if (header.find("GET") != 0) {
		throw WrongFormatException("parseHeader supports only GET");
	}
	h.type = "GET";
	h.path = header.substr(f + 1, l - f - 1);
	h.version = header.substr(l + 1, header.find_first_of('\r') - l - 1);


	while ((f=r+2, r=header.find_first_of('\r',f), l=r-1, f < l)) {
	  size_t col = header.find_first_of(':', f);
	  string key = header.substr(f, col-f);
		//if (header.at(col+1) == ' ') ++col;
		col = header.find_first_not_of(" \t", col+1);
	  string value = header.substr(col, l-col+1);
		h.content.insert(make_pair(key, value));
	}
	return h;
}
*/

/*static
string getHeaderType(const string &header) {
  size_t i = header.find(' ');
	if (i == header.npos)
		throw WrongFormatException("header type");
	return header.substr(0, i);
}

static
string getHeaderPath(const string &header) {
  string t = getHeaderType(header);
	if (htype == "GET") {
		string path = header.substr();
	} else {
		throw WrongFormatException("getHeaderPath supports only GET");
	}
}*/






static
string recvToString(SOCKET a) {
  int size;
  char buf[4];
	
	if ((size = recv(a, buf, sizeof buf - 1, 0)) < 0)
		throw SocketException("in recv");
	if (size == 0)
		throw SocketException("recv received 0 bytes");

	buf[size] = '\0';

	if (strlen(buf) != (size_t)size)
		throw BadRequestException("recvToString");

	return buf;
}



struct Request {
	string
		type,
		path,
		version;

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

	void set_10(const string &line, size_t sp_first, size_t sp_last) {
		version = line.substr(sp_last + 1, line.find('\r') - sp_last - 1);
		path = line.substr(sp_first + 1, sp_last - sp_first - 1);
		correct_path();
	}

	// HTTP 0.9
	Request(const string &line, int version, int sp_first, int sp_last) {
		type = line.substr(0, sp_first);

		if (version == 9  &&  type != "GET")
			throw BadRequestException("HTTP/0.9 request must be GET");

		if (version == 10  &&  type != "GET")
			throw NotImplementedException("supported only GET");

		if (version == 9) set_09(line, sp_first);
		else if (version == 10) set_10(line, sp_first, sp_last);

		if (path.find('/') != 0)
			throw BadRequestException("HTTP request must contain absolute path");
	}
};


static
Request receiveRequest(SOCKET a) {
  string s, all;
  size_t sp_first, sp_last;

	for (;;) {
		s = recvToString(a);
		all += s;

	  size_t r = all.find("\r\n");
		if (r != s.npos) {
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
	while ((end = all.find("\r\n\r\n")) == all.npos)
		all += recvToString(a);

	if (end != all.length() - 4)
		throw BadRequestException("receiveHTTPRequest");

	return Request(all, 10, sp_first, sp_last);
}




/*
static
Request receiveRequest(SOCKET a) {
  Request r;
  string request = receiveHTTPRequest(a);			// "GET / HTTP..."  ("GET /")
  size_t sp = request.find_first_of(' ');			// sp = 3
	if (sp == request.npos)
		throw WrongFormatException("header");
  size_t end = request.find_first_of(' ', sp+1);	// end = 5  (end = npos)
	if (end != request.npos)
		request.erase(end);							// "GET /"
	r.path = request.substr(sp + 1);				// "/"
	r.type = request.substr(0, sp);					// "GET"
	return r;
}
*/






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
  SOCKET a;
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
				closesocket(a);
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
		if (closesocket(a))
			throw SocketException("in closesocket");
	}
}






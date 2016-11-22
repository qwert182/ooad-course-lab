#include "HTTPView.h"


#include <memory.h>
#include <string.h>

#include <string>
#include <map>
#include <fstream>


#include <signal.h>


#include "../../utils/Exception.h"



class SocketException : public HTTPException {
public:
	SocketException(const char *what) : HTTPException(what) {}
};

class WrongFormatException : public HTTPException {
public:
	WrongFormatException(const char *what) : HTTPException(what) {}
};

class NotFoundException : public HTTPException {
public:
	NotFoundException(const char *what) : HTTPException(what) {}
	NotFoundException(const std::string &what) : HTTPException(what.c_str()) {}
};



using std::string;
using std::map;
using std::make_pair;
using std::ifstream;



static
map<string, string> init_from_array() {
  map<string, string> m;
	m.insert(make_pair("/", "html/index.htm"));
	m.insert(make_pair("/style", "html/style.css"));
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

	buf[size] = '\0';

	if (strlen(buf) != (size_t)size)
		throw WrongFormatException("recvToString");

	return buf;
}


static
string receiveHTTPRequest(SOCKET a) {
  string line, s, all;

	for (;;) {
		s = recvToString(a);
		all += s;

	  size_t r = s.find_first_of('\r');
		if (r != s.npos) {
			line += s.substr(0, r);
			break;
		}
		line += s;
	}

  size_t end;
	while ((end = all.find("\r\n\r\n")) == all.npos)
		all += recvToString(a);

	if (end != all.length() - 4)
		throw WrongFormatException("receiveHTTPRequest");

	return line;
}




struct Request {
	string
		type,
		path;
};



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







void send_file(SOCKET a, const string &filename) {
  char buf[1000];
  int size;
  ifstream f(filename, std::ios::binary);

	if (!f.good())
		throw NotFoundException("can't open file \"" + filename + "\"");

	while ((f.read(buf, sizeof(buf)),  (size = (int)f.gcount()) != 0)) {
		if (send(a, buf, size, 0) != size)
			throw SocketException("in send");
	}
}

#include <iostream>

using std::cout;
using std::endl;


void HTTPView::server() {
  SOCKET a;
  union {sockaddr a; sockaddr_in i;} addr;
  int addr_len;


	if (listen(s, 2))
		throw SocketException("in listen");

	for (;;) {
		addr_len = sizeof addr.a;
		memset(&addr, 0, sizeof addr.a);

		current_socket = s; // global variable
		if ((a = accept(s, &addr.a, &addr_len)) == INVALID_SOCKET) {
			if (has_control_c_pressed) // global variable
				break;
			throw SocketException("in accept");
		}

		cout << "accept" << endl;


		Request request = receiveRequest(a);
		cout << "request\n";
		cout << "\t" << request.type <<"\n";
		cout << "\t" << request.path << endl;

		if (request.type == "GET") {
			auto found = path_to_file.find(request.path);
			if (found != path_to_file.end()) {
				send_file(a, found->second);
				cout << "sended\n";
				cout << "\t\"" << found->second << '"' << endl;
			}
		}

		if (closesocket(a))
			throw SocketException("in closesocket");
	}
}






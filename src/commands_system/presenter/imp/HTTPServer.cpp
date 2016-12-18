#include "HTTPServer.h"


#include <signal.h>

#include "HTTPException.h"
#include "SocketException.h"
#include "StatusHTTPException.h"

#include "utils/request.h"
#include "utils/send.h"


#include <type_traits>
#include "../../utils/formatTypeidName.h"



#include "IResource.h"
#include "Session.h"


#include <iostream>


using std::cout;
using std::endl;




static
SOCKET current_socket;

static
bool has_control_c_pressed = false;

static
void on_control_c_pressed(int) { // shortly double hit ctrl^c causes abort() message
	closesocket(current_socket);
	has_control_c_pressed = true;
}





HTTPServer::HTTPServer() {
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

	IResource::Init();
	Session::InitAll();
}




HTTPServer::~HTTPServer() {
	signal(SIGINT, SIG_DFL);

	Session::DisposeAll();
	IResource::Dispose();

	if (closesocket(s))
		if (!has_control_c_pressed)
			throw SocketException("in closesocket");

	if (WSACleanup())
		throw SocketException("in WSACleanup");
}





void HTTPServer::present() {
	server();
}



void HTTPServer::server() {
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


		  Request request = Request::receive(a);
			cout << "request\n";
			cout << "\t\"" << request.type << "\"\n";
			cout << "\t\"" << request.path << '\"' << endl;
			cout << '{';
			cout << request.all;
			cout << '}' << endl;


			send_data(a, IResource::perform(request));

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

			send_status(a, e.getStatus());
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


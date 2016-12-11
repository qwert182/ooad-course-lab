#include "send.h"

#include <fstream>
#include "NotFoundException.h"
#include "SocketException.h"

using std::string;
using std::ifstream;


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


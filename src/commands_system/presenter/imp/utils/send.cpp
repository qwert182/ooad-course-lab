#include "send.h"

#include <fstream>
#include <vector>
#include "../NotFoundException.h"
#include "../SocketException.h"

#include "status.h"
#include "append.h"

using std::string;
using std::ifstream;
using std::vector;
using std::string;




void send_data(SOCKET a, const vector<char> &data) {
  static const size_t part_size = 1000;
  const int
	  size = static_cast<int>(data.size()),
	  full_parts_size = (size / part_size) * part_size,
	  last_part_size = size - full_parts_size;

  int i;

	for (i = 0; i < full_parts_size; i += part_size) {
		if (send(a, &data[i], part_size, 0) != part_size)
			throw SocketException("in send_data");
	}

	if (last_part_size != 0)
		if (send(a, &data[i], last_part_size, 0) != last_part_size)
			throw SocketException("in send_data");
}




void send_status(SOCKET a, int code) {
  vector<char> line = getStatusBy(code);
	appendCRLF(line);
  	send_data(a, line);
}


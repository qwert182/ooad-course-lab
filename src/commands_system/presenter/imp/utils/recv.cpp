#include "recv.h"

#include <algorithm>
#include "../SocketException.h"
#include "../BadRequestException.h"


using std::vector;
using std::string;
using std::find;
using std::search;


void recvToVector(SOCKET a, vector<char> &data) {
  int size;
  char buf[4];
	
	if ((size = recv(a, buf, sizeof buf, 0)) < 0)
		throw SocketException("in recv");
	if (size == 0)
		throw SocketException("recv received 0 bytes");

	data.insert(data.end(), buf, &buf[size]);
}






static
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




string recvToVector_MoveNewToString(SOCKET a, vector<char> &data) {
  size_t last_size = data.size();
	recvToVector(a, data);
	return moveNewDataToString(data, last_size, "\r\n\r\n");
}



#include "status.h"

#include <stdio.h>
#include <algorithm>

#include "../InternalServerErrorException.h"

using std::vector;
using std::find_if;


struct stat_t {
	int code;
	const char *reason;
};

static
const stat_t statuses[] = {
	{200, "OK"},
	{302, "Moved Temporarily"},
	{303, "See Other"},
	{400, "Bad Request"},
	{403, "Forbidden"},
	{404, "Not Found"},
	{500, "Internal Server Error"},
	{501, "Not Implemented"}
};


class CodeEquals {
	int code;
public:
	CodeEquals(int code) : code(code) {}
	bool operator() (const stat_t &status) {
		return status.code == code;
	}
};


vector<char> getStatusBy(int code) {
  static const stat_t
	  *begin = statuses,
	  *end = &statuses[sizeof statuses/sizeof*statuses];
  char buf[100];

	const stat_t *found = find_if(begin, end, CodeEquals(code));
	if (found == end)
		throw InternalServerErrorException("in getStatusBy");

  const char *reason = found->reason;

  size_t size = sprintf(buf, "HTTP/1.1 %d %s\r\n", code, reason);
	return vector<char>(buf, buf + size);
}


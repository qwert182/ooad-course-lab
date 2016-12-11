#include "../trim.h"

using std::string;

void trim(string &s) {
	static const char spaces[] = " \t";
	size_t start = s.find_first_not_of(spaces);
	s.erase(0, start);
	size_t end = s.find_last_not_of(spaces);
	if (end != string::npos)
		s.erase(end + 1);
}


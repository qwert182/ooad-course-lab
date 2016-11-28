#include "common.h"
#include "../DataBaseException.h"

#include <algorithm>

using std::vector;
using std::string;
using std::find;

size_t findColumnIndexByColumnName(const vector<string> &hat, const string &name) {
  auto found = find(hat.begin(), hat.end(), name);
  size_t j;
	if (found == hat.end())
		throw DataBaseException("table doesn't contain column \"" + name + '"');

	j = found - hat.begin();
	return j;
}


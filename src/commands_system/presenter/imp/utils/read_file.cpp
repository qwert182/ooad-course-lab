#include "read_file.h"

#include "../NotFoundException.h"
#include <fstream>
#include <string>

using std::string;
using std::vector;
using std::ifstream;
using std::ios;


vector<char> read_file(const char *filename) {
  ifstream f(filename, ios::binary);
	if (!f.good())
		throw NotFoundException("read_file(\"" + string(filename) + "\")");
	f.seekg(0, ios::end);
  size_t size = static_cast<size_t>(f.tellg());
	f.seekg(0, ios::beg);
  vector<char> result(size);
	if (size != 0)
		f.read(&result[0], size);
	return result;
}


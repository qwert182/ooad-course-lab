#include "common.h"
#include "../DataBaseException.h"

#include <algorithm>
#include <fstream>

using std::vector;
using std::string;
using std::find;
using std::ios;
using std::ifstream;
using std::ofstream;


size_t findColumnIndexByColumnName(const vector<string> &hat, const string &name) {
  auto found = find(hat.begin(), hat.end(), name);
  size_t j;
	if (found == hat.end())
		throw DataBaseException("table doesn't contain column \"" + name + '"');

	j = found - hat.begin();
	return j;
}




#ifdef COMPILE_WITH_TESTS
	void __copy_backup_test() {
		if (!__copy_file("data_backup/test.txt", "data_test/test.txt"))
			throw DataBaseException("can't copy \"data_backup/test.txt\" to \"data_test/test.txt\"");
	}

	void __delete_backup_test() {
		if (_unlink("data_test/test.txt"))
			throw DataBaseException("can't delete \"data_test/test.txt\"");
	}


	bool __copy_file(const char src[], const char dst[]) {
		ifstream i(src, ios::binary);
		if (!i.good()) return false;
		i.seekg(0, ios::end);
		size_t s = static_cast<size_t>(i.tellg());
		i.seekg(0, ios::beg);
		char * buf = static_cast<char *>(malloc(s));
		i.read(buf, s);
		i.close();

		ofstream o(dst, ios::binary);
		if (!o.good()) return false;
		o.write(buf, s);
		free(buf);

		return true;
	}
#endif


#pragma once

#include <vector>
#include <string>


size_t findColumnIndexByColumnName(const std::vector<std::string> &hat, const std::string &name);

#ifdef COMPILE_WITH_TESTS
	bool __copy_file(const char src[], const char dst[]);
	void __copy_backup_test();
	void __delete_backup_test();
#endif

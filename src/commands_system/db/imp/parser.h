#include <string>
#include <vector>
#include "../../utils/Exception.h"

std::vector <std::vector <std::string> > parse(std::string file_name);

class ParseFailedException : public Exception {
public:
	ParseFailedException(const char *what) : Exception(what) {}
};
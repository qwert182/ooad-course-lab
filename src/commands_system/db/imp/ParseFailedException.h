#pragma once

#include "../DataBaseException.h"
#include <string>

class ParseFailedException : public DataBaseException {
public:
	ParseFailedException(const char *what) : DataBaseException(what) {}
	ParseFailedException(const std::string &what) : DataBaseException(what.c_str()) {}
};


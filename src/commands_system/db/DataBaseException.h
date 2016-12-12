#pragma once

#include "../utils/Exception.h"
#include <string>


class DataBaseException : public Exception {
public:
	DataBaseException(const char *what) : Exception(what) {}
	DataBaseException(const std::string &what) : Exception(what.c_str()) {}
};


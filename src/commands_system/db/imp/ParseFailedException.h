#pragma once

#include "../DataBaseException.h"

class ParseFailedException : public DataBaseException {
public:
	ParseFailedException(const char *what) : DataBaseException(what) {}
};


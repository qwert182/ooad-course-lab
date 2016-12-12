#pragma once

#include "../DataBaseException.h"

class WriteFailedException : public DataBaseException {
public:
	WriteFailedException(const char *what) : DataBaseException(what) {}
};


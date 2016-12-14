#pragma once
#include "StatusHTTPException.h"

class InternalServerErrorException : public StatusHTTPException {
public:
	InternalServerErrorException(const char *what) : StatusHTTPException(what, 500) {}
};


#pragma once
#include "StatusHTTPException.h"

class BadRequestException : public StatusHTTPException {
public:
	BadRequestException(const char *what) : StatusHTTPException(what, 400) {}
};


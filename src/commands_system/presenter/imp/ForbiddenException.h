#pragma once
#include "StatusHTTPException.h"

class ForbiddenException : public StatusHTTPException {
public:
	ForbiddenException(const char *what) : StatusHTTPException(what, 403) {}
};


#pragma once
#include "StatusHTTPException.h"

class NotFoundException : public StatusHTTPException {
public:
	NotFoundException(const char *what) : StatusHTTPException(what, 404) {}
	NotFoundException(const std::string &what) : StatusHTTPException(what.c_str(), 404) {}
};


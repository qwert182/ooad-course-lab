#pragma once
#include "StatusHTTPException.h"

class NotImplementedException : public StatusHTTPException {
public:
	NotImplementedException(const char *what) : StatusHTTPException(what, 501) {}
};


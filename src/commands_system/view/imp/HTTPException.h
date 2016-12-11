#pragma once
#include "../../utils/Exception.h"

class HTTPException : public Exception {
public:
	HTTPException(const char *what) : Exception(what) {}
};


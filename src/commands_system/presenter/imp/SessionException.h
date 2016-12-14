#pragma once
#include "HTTPException.h"

class SessionException : public HTTPException {
public:
	SessionException(const char *what) : HTTPException(what) {}
};


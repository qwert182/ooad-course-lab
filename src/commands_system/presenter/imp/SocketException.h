#pragma once
#include "HTTPException.h"

class SocketException : public HTTPException {
public:
	SocketException(const char *what) : HTTPException(what) {}
};


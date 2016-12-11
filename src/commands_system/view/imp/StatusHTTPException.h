#pragma once
#include "HTTPException.h"

class StatusHTTPException : public HTTPException {
	int status;
public:
	int getStatus() const {
		return status;
	}

	StatusHTTPException(const char *what, int status) : HTTPException(what), status(status) {}
};


#pragma once

#include "Exception.h"

class AssertionFailedException : public Exception {
public:
	AssertionFailedException(const char *what) : Exception(what) {}
};


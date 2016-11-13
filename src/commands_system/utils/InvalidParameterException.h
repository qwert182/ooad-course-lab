#pragma once
#include "Exception.h"

class InvalidParameterException: public Exception {
public:
	InvalidParameterException(const char* what):Exception(what){}
};
#pragma once

#include "../utils/Exception.h"

class AccessDeniedException : public Exception {
public:
	AccessDeniedException(const char *what) : Exception(what) {}
};


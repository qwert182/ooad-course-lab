#include "../Exception.h"

#include "../strnew.h"
#include <malloc.h>


Exception::Exception(const char *what) {
	if (what)
		s = strnew(what);
	else
		s = nullptr;
}

const char * Exception::what() const {
	return s;
}

Exception::~Exception() {
	free(s);
}


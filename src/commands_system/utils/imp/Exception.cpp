#include "../Exception.h"

#include "../strnew.h"
#include <malloc.h>



void Exception::init(const char *what) {
	if (what)
		s = strnew(what);
	else
		s = nullptr;
}



Exception::Exception(const char *what) {
	init(what);
}


Exception::Exception(const Exception &e) {
	init(e.s);
}

Exception & Exception::operator =(const Exception &e) {
	free(s);
	init(e.s);
	return *this;
}

Exception::Exception(Exception &&e) {
	s = e.s;
	e.s = nullptr;
}

Exception & Exception::operator =(Exception &&e) {
  char *tmp = s;
	s = e.s;
	e.s = tmp;
	return *this;
}



Exception::~Exception() {
	free(s);
}



const char * Exception::what() const {
	return s;
}


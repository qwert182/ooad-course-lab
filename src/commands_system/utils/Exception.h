#pragma once

class Exception {
	char *s;
	void init(const char *what);
public:
	Exception(const char *what);
	Exception(const Exception &);
	Exception & operator =(const Exception &);
	Exception(Exception &&);
	Exception & operator =(Exception &&);
	virtual const char * what() const;
	virtual ~Exception();
};


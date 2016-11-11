#pragma once

class Exception {
	char *s;
protected:
	Exception(const char *what);
public:
	virtual const char * what() const;
	virtual ~Exception();
};


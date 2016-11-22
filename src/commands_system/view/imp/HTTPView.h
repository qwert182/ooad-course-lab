#pragma once

#include "../IView.h"
#include "../../utils/Exception.h"
#include <map>
#include <string>
#include <winsock.h>


class HTTPView : public IView {
private:
	SOCKET s;
	const std::map<std::string, std::string> path_to_file;

	// disable
	HTTPView(const HTTPView &);
	HTTPView & operator =(const HTTPView &);


public:
	HTTPView();
	void server();
	virtual ~HTTPView();
};


class HTTPException : public Exception {
public:
	HTTPException(const char *what) : Exception(what) {}
};

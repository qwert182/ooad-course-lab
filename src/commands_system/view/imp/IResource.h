#pragma once

#include <vector>
#include <winsock.h>

class IResource {
	IResource(const IResource &);
	IResource & operator =(const IResource &);

	static void notImplemented();
protected:
	IResource() {}
public:
	virtual void get(SOCKET) const {notImplemented();}
	virtual void post(SOCKET, const std::vector<char> &) const {notImplemented();}
	virtual ~IResource() {}


	static void perform(const struct Request &, SOCKET);
	static void init();
	static void dispose();
};


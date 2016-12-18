#pragma once

#include <vector>
#include "Session.h"

class IResource {
	IResource(const IResource &);
	IResource & operator =(const IResource &);

	static std::vector<char> notImplemented();
protected:
	IResource() {}
public:
	virtual std::vector<char> get(Session *) const {return notImplemented();}
	virtual std::vector<char> post(const std::vector<char> &, Session *) const {return notImplemented();}
	virtual ~IResource() {}


	static std::vector<char> perform(const struct Request &);
	static void Init();
	static void Dispose();
};


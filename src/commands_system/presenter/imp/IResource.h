#pragma once

#include <vector>

class IResource {
	IResource(const IResource &);
	IResource & operator =(const IResource &);

	static std::vector<char> notImplemented();
protected:
	IResource() {}
public:
	virtual std::vector<char> get() const {return notImplemented();}
	virtual std::vector<char> post(const std::vector<char> &) const {return notImplemented();}
	virtual ~IResource() {}


	static std::vector<char> perform(const struct Request &);
	static void init();
	static void dispose();
};


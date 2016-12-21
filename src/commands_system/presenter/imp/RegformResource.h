#pragma once

#include "IResource.h"

class RegformResource : public IResource {
	RegformResource(const RegformResource &);
public:
	RegformResource();
	virtual std::vector<char> get(Session *) const;
	virtual std::vector<char> post(const std::vector<char> &content, Session *) const;
	virtual ~RegformResource() {}
};


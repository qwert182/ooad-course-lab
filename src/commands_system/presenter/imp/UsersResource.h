#pragma once

#include "IResource.h"

class UsersResource : public IResource {
	UsersResource(const UsersResource &);
public:
	UsersResource();

	virtual std::vector<char> post(const std::vector<char> &, Session *) const;
	virtual ~UsersResource() {}
};


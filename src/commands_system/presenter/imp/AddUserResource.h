#pragma once

#include "IResource.h"

class AddUserResource : public IResource {
	AddUserResource(const AddUserResource &);
public:
	AddUserResource();
	virtual std::vector<char> post(const std::vector<char> &content, Session *) const;
	virtual ~AddUserResource() {}
};


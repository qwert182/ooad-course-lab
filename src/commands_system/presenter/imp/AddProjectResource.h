#pragma once

#include "IResource.h"

class AddProjectResource : public IResource {
	AddProjectResource(const AddProjectResource &);
public:
	AddProjectResource();
	virtual std::vector<char> get(Session *) const;
	virtual std::vector<char> post(const std::vector<char> &content, Session *) const;
	virtual ~AddProjectResource() {}
};


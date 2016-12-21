#pragma once

#include "IResource.h"

class AddTaskResource : public IResource {
	AddTaskResource(const AddTaskResource &);
public:
	AddTaskResource();
	virtual std::vector<char> get(Session *) const;
	virtual std::vector<char> post(const std::vector<char> &content, Session *) const;
	virtual ~AddTaskResource() {}
};


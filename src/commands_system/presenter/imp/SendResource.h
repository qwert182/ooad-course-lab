#pragma once

#include "IResource.h"

class SendResource : public IResource {
	SendResource(const SendResource &);
public:
	SendResource();

	virtual std::vector<char> post(const std::vector<char> &, Session *) const;
	virtual ~SendResource() {}
};


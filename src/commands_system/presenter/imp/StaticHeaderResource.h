#pragma once

#include "IResource.h"

class StaticHeaderResource : public IResource {
	const char *header;
	int status;

	StaticHeaderResource(const StaticHeaderResource &);
public:
	StaticHeaderResource(int status, const char *header);
	virtual std::vector<char> get(Session *) const;
	virtual ~StaticHeaderResource() {}
};


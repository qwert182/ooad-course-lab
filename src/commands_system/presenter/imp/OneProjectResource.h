#pragma once

#include "IResource.h"

class OneProjectResource : public IResource {
	OneProjectResource(const OneProjectResource &);
public:
	OneProjectResource();
	virtual std::vector<char> get(Session *) const;
	virtual std::vector<char> post(const std::vector<char> &, Session *) const;
	virtual ~OneProjectResource() {}
};


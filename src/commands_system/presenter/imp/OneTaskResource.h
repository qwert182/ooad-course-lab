#pragma once

#include "IResource.h"

class OneTaskResource : public IResource {
	OneTaskResource(const OneTaskResource &);
public:
	OneTaskResource();
	virtual std::vector<char> get(Session *) const;
	virtual std::vector<char> post(const std::vector<char> &, Session *) const;
	virtual ~OneTaskResource() {}
};


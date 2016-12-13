#pragma once

#include "IResource.h"

class LoginActionResource : public IResource {
	LoginActionResource(const LoginActionResource &);
public:
	LoginActionResource();
	virtual std::vector<char> get() const;
	virtual std::vector<char> post(const std::vector<char> &content) const;
	virtual ~LoginActionResource() {}
};


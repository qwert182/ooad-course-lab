#pragma once

#include "IResource.h"

class LoginActionResource : public IResource {
	LoginActionResource(const LoginActionResource &);
public:
	LoginActionResource();
	virtual std::vector<char> get(Session *) const;
	virtual std::vector<char> post(const std::vector<char> &content, Session *) const;
	virtual ~LoginActionResource() {}
};


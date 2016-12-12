#pragma once

#include "IResource.h"

class LoginActionResource : public IResource {
	LoginActionResource(const LoginActionResource &);
public:
	LoginActionResource();
	virtual void post(SOCKET, const std::vector<char> &content) const;
	virtual ~LoginActionResource() {}
};


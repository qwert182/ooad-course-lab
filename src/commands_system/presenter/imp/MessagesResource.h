#pragma once

#include "IResource.h"

class MessagesResource : public IResource {
	MessagesResource(const MessagesResource &);
public:
	MessagesResource();
	virtual std::vector<char> get(Session *) const;
	virtual std::vector<char> post(const std::vector<char> &, Session *) const;
	virtual ~MessagesResource() {}
};


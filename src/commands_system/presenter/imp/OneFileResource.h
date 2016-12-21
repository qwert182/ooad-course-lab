#pragma once

#include "IResource.h"

class OneFileResource : public IResource {
	std::string file_name;
	OneFileResource(const OneFileResource &);
public:
	OneFileResource(const std::string & file_name);
	virtual std::vector<char> get(Session *) const;
	virtual std::vector<char> post(const std::vector<char> &, Session *) const;
	virtual ~OneFileResource() {}
};


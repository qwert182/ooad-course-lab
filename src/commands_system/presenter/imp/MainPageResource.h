#pragma once

#include "IResource.h"

class MainPageResource : public IResource {
	MainPageResource(const MainPageResource &);
public:
	MainPageResource();
	virtual std::vector<char> get(Session *) const;
	virtual ~MainPageResource() {}
};


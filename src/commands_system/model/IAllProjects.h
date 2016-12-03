#pragma once
#include <vector>

class IAllProjects {
public:
	virtual std::vector<class IProject *> getProjects() const = 0;
	virtual void add(const class IProject &project) = 0;
};


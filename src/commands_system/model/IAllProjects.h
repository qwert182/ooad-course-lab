#pragma once
#include <vector>
#include <string>

class IAllProjects {
public:
	virtual std::vector<class IProject *> getProjects() const = 0;
	virtual class IProject * getProjectByName(const std::string &name) const = 0;
	virtual void add(const class IProject &project) = 0;
	virtual ~IAllProjects() {}
};


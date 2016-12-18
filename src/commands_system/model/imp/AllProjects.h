#pragma once

#include "../IAllProjects.h"
#include "../IUser.h"
#include "User.h"

#include <vector>

class AllProjects : public IAllProjects {
private: 
	const User *user;

public: 
	AllProjects(const User *user);
	virtual std::vector<class IProject *> getProjects() const;
	virtual void add(const class IProject &project);
};
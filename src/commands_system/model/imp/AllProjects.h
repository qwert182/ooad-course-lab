#pragma once

#include "../IAllProjects.h"
#include "../IUser.h"
#include "User.h"

#include <vector>

class AllProjects : public IAllProjects {
private: 
	User *user;

public: 
	AllProjects(User *user);
	virtual std::vector<class IProject *> getProjects() const;
	virtual void add(const class IProject &project);
};
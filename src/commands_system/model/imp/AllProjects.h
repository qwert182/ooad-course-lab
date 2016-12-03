#pragma once
#include "../IAllProjects.h"
#include <vector>
#include "../IUser.h"


class AllProjects : public IAllProjects
{
private: IUser *user;

public: AllProjects(const IUser &user);
		virtual std::vector<class IProject *> getProjects() const;
		virtual void add(const class IProject &project);
};
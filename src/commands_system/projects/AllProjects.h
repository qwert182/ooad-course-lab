#pragma once
#include <vector>
using namespace std;
class AllProjects
{
private: IUser user;

public: AllProjects(IUser user);
		virtual vector<IProject> getProjects() const;
		virtual void add(IProject project) const;
};
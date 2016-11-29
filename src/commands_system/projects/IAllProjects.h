#pragma once

#include "IProject.h"

class IAllProjects
{
	public:virtual vector<IProject> getProjects() const = 0;
		   virtual void add(IProject project) const = 0;
};
#pragma once

#include <string>
#include <vector>
using namespace std;

class IProject
{
public: virtual string getName() const = 0;
		virtual void setName(string name) const = 0;
		virtual string getDescription() const = 0;
		virtual void setDescription(string description) const = 0;
		virtual vector<IUser> getWorkers() const = 0;
		virtual void add(IUser worker) const = 0;
		virtual vector<ITask> getTasks() const = 0;
		virtual void add(ITask task) const = 0;
};
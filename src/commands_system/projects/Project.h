#pragma once

#include <string>
#include <vector>
using namespace std;
class Project
{
private: int id;

public: Project(int id);
		Project(string name, string description);

		virtual string getName() const;
		virtual void setName(string name) const;
		virtual string getDescription() const;
		virtual void setDescription(string description) const;
		virtual vector<IUser> getWorkers() const;
		virtual void add(IUser worker) const;
		virtual vector<ITask> getTasks() const;
		virtual void add(ITask task) const;
};
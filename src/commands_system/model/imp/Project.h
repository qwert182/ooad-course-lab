#pragma once

#include <string>
#include <vector>
#include "../IProject.h"

class Project :public IProject {
private: 
	int id;

public: 
	Project(int id);
	Project(std::string name, std::string description);
	
	virtual std::string getName() const;
	virtual void setName(const std::string &name);
	
	virtual std::string getDescription() const;
	virtual void setDescription(const std::string &description);
	
	virtual std::vector<class IUser *> getWorkers() const;
	virtual void add(const class IUser &worker);
	
	virtual std::vector<class ITask *> getTasks() const;
	virtual void add(const class ITask &task);
	virtual class ITask * getTaskByName(const std::string &) const;
};


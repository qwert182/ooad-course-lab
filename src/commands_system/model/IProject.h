#pragma once

#include <string>
#include <vector>


class IProject
{
public: virtual std::string getName() const = 0;
		virtual void setName(const std::string &name)  = 0;

		virtual std::string getDescription() const = 0;
		virtual void setDescription(const std::string &description)  = 0;
		
		virtual std::vector<class IUser *> getWorkers() const = 0;
		virtual void add(const class IUser &worker)  = 0;
		
		virtual std::vector<class ITask *> getTasks() const = 0;
		virtual void add(const class ITask &task) = 0;
		virtual class ITask * getTaskByName(const std::string &) const = 0;
};
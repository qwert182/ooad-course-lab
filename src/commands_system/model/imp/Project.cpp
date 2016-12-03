#include "Project.h"

using namespace std;
Project::Project(int id) {}
Project::Project(string name, string description) {}

string Project::getName() const 
{
	string name;
	return name;
}
void Project::setName(const std::string &name){}

string Project::getDescription() const 
{
	string description;
	return description;
}
void Project::setDescription(const std::string &description) {}

vector<class IUser *>  Project::getWorkers() const 
{
	vector< class IUser *> result;
	return result;
}
void Project::add(const class IUser &worker) {}

vector<class ITask *> Project::getTasks() const 
{
	vector<class ITask *> result;
	return result;
}
void Project::add(const class ITask &task){}
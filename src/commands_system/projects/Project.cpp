#include "Project.h"

Project::Project(int id) 
{
	this->id = id;
}
Project::Project(string name, string description) 
{
	setName(name);
	setDescription(description);
}

string Project::getName() const 
{

}
void Project::setName(string name) const 
{

}
string Project::getDescription() const 
{

}
void Project::setDescription(string description) const 
{

}
vector<IUser> Project::getWorkers() const
{

}
void Project::add(IUser worker) const
{

}
vector<ITask> Project::getTasks() const 
{

}
void Project::add(ITask task) const
{

}
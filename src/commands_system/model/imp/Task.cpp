#include "Task.h"
using namespace std;

Task::Task(int id) {}
Task::Task(string name, string description, string theme) {}

string Task::getName() const 
{
	string name;
	return name;
}
void Task::setName(const std::string &name) {}

string Task::getTheme() const 
{
	string Theme;
	return Theme;
}
void Task::setTheme(const std::string &theme) {}

string Task::getDescription() const 
{
	string description;
	return description;
}
void Task::setDescription(const std::string &description) {}

vector<class INote *> Task::getNotes() const 
{
	vector< class INote *> result;
	return result;
}
void Task::add(const class INote &note) {}

vector<class IAttachment *> Task::getAttachments() const 
{
	vector< class IAttachment *> result;
	return result;
}
void Task::add(const class IAttachment &attachments) {}
#include "Task.h"
#include <vector>

Task::Task(int id) {}
Task::Task(string name, string description, string theme) {}

string Task::getName() const {}
void Task::setName(string name) const {}
string Task::getTheme() const {}
void Task::setTheme(string theme) const {}
string Task::getDescription() const {}
void Task::setDescription(string description) const {}

vector<INote> Task::getNotes() const {}
void Task::add(INote note) const {}

vector<IAttachment> Task::getAttachments() const {}
void Task::add(IAttachment attachments) const {}
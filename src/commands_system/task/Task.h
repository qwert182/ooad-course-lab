#pragma once
#include <string>
using namespace std;
class Task
{
private: int id;
public:
	Task(int id);
	Task(string name, string description, string theme);

	virtual string getName() const;
	virtual void setName(string name) const;
	virtual string getTheme() const;
	virtual void setTheme(string theme) const;
	virtual string getDescription() const;
	virtual void setDescription(string description) const;

	virtual vector<INote> getNotes() const;
	virtual void add(INote note) const;

	virtual vector<IAttachment> getAttachments() const;
	virtual void add(IAttachment attachments) const;
};
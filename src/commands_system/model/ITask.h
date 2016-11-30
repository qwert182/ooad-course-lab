#pragma once
#include <string>
#include <vector>
using namespace std;
class ITask
{
public:
	virtual string getName() const = 0;
	virtual void setName(string name) const = 0;
	virtual string getTheme() const = 0;
	virtual void setTheme(string theme) const = 0;
	virtual string getDescription() const = 0;
	virtual void setDescription(string description) const = 0;

	virtual vector<INote> getNotes() const = 0;
	virtual void add(INote note) const = 0;

	virtual vector<IAttachment> getAttachments() const = 0;
	virtual void add(IAttachment attachments) const = 0;
};
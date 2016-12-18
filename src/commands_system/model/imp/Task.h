#pragma once
#include <string>
#include <vector>
#include "../ITask.h"

class Task: public ITask
{
private: int id;

public:
	Task(int id);
	Task(std::string name, std::string theme, std::string description);

	virtual std::string getName() const;
	virtual void setName(const std::string &name);

	virtual std::string getTheme() const;
	virtual void setTheme(const std::string &theme);

	virtual std::string getDescription() const;
	virtual void setDescription(const std::string &description);

	virtual std::vector<class INote *> getNotes() const;
	virtual void add(const class INote &note);

	virtual std::vector<class IAttachment *> getAttachments() const;
	virtual void add(const class IAttachment &attachments);

	int getId() const;
};
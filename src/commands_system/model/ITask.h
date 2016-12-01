#pragma once
#include <string>
#include <vector>


class ITask
{
public:
	virtual std::string getName() const = 0;
	virtual void setName(const std::string &name) = 0;
	
	virtual std::string getTheme() const = 0;
	virtual void setTheme(const std::string &theme) = 0;
	
	virtual std::string getDescription() const = 0;
	virtual void setDescription(const std::string &description) = 0;

	virtual std::vector<class INote *> getNotes() const = 0;
	virtual void add(const class INote &note) = 0;

	virtual std::vector<class IAttachment *> getAttachments() const = 0;
	virtual void add(const class IAttachment &attachments) = 0;
};
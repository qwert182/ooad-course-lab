#pragma once

#include <string>
#include <vector>

class INote {
public:
	virtual class IUser * getWriter() const = 0;
	virtual void add(const class IAttachment &attachment) = 0;
	virtual std::string getText() const = 0;	
	virtual std::vector<class IAttachment *> getAttachments() const = 0;
};


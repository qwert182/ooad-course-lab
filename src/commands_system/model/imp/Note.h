#pragma once
#include <string>
#include <vector>
#include "../INote.h"

class Note: public INote {
private: 
	int id;

public:
	Note(int id);
	Note(const IUser &writer, const std::string &text);

	virtual class IUser * getWriter() const;
	virtual void add(const class IAttachment &attachment);	
	virtual std::string getText() const;
	virtual std::vector<class IAttachment *> getAttachments() const;

	int getId() const;
};
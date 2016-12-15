#pragma once
#include <string>
#include "../IAttachment.h"

class Attachment: public IAttachment {
private: 
	int id;

public: 
	Attachment(int id);
	Attachment(const std::string &fileName, const std::string &description, const IUser &owner);

	virtual std::string getFileName() const;
	virtual std::string getDescription() const;
	virtual class IUser * getOwner() const;

	int getId() const;
};
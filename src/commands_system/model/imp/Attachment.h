#pragma once
#include <string>
#include "../IAttachment.h"

class Attachment: public IAttachment
{
private: int id;
public: Attachment(int id);
		Attachment(std::string const &file, IUser const &desc);
		
		virtual std::string getFileName() const;
		virtual std::string getDescription() const;
		virtual class IUser * getOwner() const;
};
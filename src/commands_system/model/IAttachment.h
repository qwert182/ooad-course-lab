#pragma once
#include <string>


class IAttachment
{
public: virtual std::string getFileName() const = 0;
		virtual std::string getDescription() const = 0;
		virtual class IUser * getOwner() const = 0;
};
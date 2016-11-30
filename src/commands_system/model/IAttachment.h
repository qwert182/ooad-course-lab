#pragma once
#include <string>
using namespace std;
class IAttachment
{
public: virtual string getFileName() const = 0;
		virtual string getDescription() const = 0;
		virtual IUser getOwner() const = 0;
};
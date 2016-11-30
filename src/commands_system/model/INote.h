#pragma once
#include <string>
#include <vector>
using namespace std;
class INote
{
public:
	virtual IUser getWriter() const = 0;
	virtual string getText() const = 0;
	virtual vector<IAttachment> getAttachments() const = 0;
};
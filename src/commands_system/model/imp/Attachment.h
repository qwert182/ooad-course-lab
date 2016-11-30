#pragma once
#include <string>
using namespace std;

class Attachment
{
private: int id;
public: Attachment(int id);
		Attachment(string file, IUser desc);
		virtual string getFileName() const;
		virtual string getDescription() const;
		virtual IUser getOwner() const;
};
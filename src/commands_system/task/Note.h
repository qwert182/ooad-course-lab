#pragma once
#include<string>
using namespace std;
class Note
{
private: int id;
public: Note(int id);
		Note(IUser writer, string text);
		void add(IAttachment attachment);
		virtual IUser getWriter() const;
		virtual string getText() const;
		virtual vector<IAttachment> getAttachments() const;
};
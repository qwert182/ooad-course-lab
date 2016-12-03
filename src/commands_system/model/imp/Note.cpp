#include "Note.h"

using namespace std;
Note::Note(int id)
{}
Note::Note(IUser const &writer, string const &text)
{}
void Note::add(const IAttachment &attachment)
{}



IUser* Note::getWriter() const 
{
	IUser * Writer;
	return Writer;
}
string Note::getText() const 
{
	string text;
	return text;
}
vector<IAttachment*> Note::getAttachments() const 
{
	vector<IAttachment *> result;
	return result;
}

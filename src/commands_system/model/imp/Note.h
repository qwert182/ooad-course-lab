#pragma once
#include <string>
#include <vector>
#include "../INote.h"

class Note: public INote
{
private: int id;

public: Note(int id);
		Note( IUser const &writer, std::string const &text);
		void add(IAttachment const &attachment);
		
		virtual class IUser *getWriter() const;
		virtual std::string getText() const;
		virtual std::vector<class IAttachment *> getAttachments() const;
};
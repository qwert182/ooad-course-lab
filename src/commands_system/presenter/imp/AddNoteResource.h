#pragma once

#include "IResource.h"

class AddNoteResource : public IResource {
	AddNoteResource(const AddNoteResource &);
public:
	AddNoteResource();

	virtual std::vector<char> post(const std::vector<char> &, Session *) const;
	virtual ~AddNoteResource() {}
};


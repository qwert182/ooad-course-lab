#pragma once

#include "Note.h"
#include "User.h"
#include "Attachment.h"
#include "dataBase.h"

using namespace std;

Note::Note(int id) { 
	this->id = id;
}

Note::Note(const IUser &writer, const string &text) {

}

void Note::add(const IAttachment &attachment) {

}

IUser * Note::getWriter() const {
	IUser *writer;

	ptrTable t = dataBase->perform(
		SELECT_ONLY("writer_id").from("notes").where("id", this->id)
	);

	int idUser = t->get(0, 0);
	writer = new User(idUser);

	return writer;
}

string Note::getText() const {
	string text;

	ptrTable t = dataBase->perform(
		SELECT_ONLY("text").from("notes").where("id", this->id)
	);

	text = t->get(0, 0);

	return text;
}

vector<IAttachment*> Note::getAttachments() const {
	vector<IAttachment *> result;

	ptrTable t = dataBase->perform(
		SELECT_ONLY("id").from("attachments").where("note_id", this->id)
	);

	int numOfAttach = t->getRowCount();
	int idAttach;
	IAttachment *attach;

	result.reserve(numOfAttach);

	for(int i = 0; i < numOfAttach; i++) {
		idAttach = t->get(i, 0);
		attach = new Attachment(idAttach);
		result.push_back(attach);
	}

	return result;
}

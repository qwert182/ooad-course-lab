#pragma once

#include "Note.h"
#include "dataBase.h"
#include "User.h"

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
	return text;
}

vector<IAttachment*> Note::getAttachments() const {
	vector<IAttachment *> result;
	return result;
}

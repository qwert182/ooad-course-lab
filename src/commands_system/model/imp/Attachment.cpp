#pragma once

#include "Attachment.h"
#include "dataBase.h"
#include "User.h"

using namespace std;

Attachment::Attachment(int id) {
	this->id = id;
}

Attachment::Attachment(string const &file, IUser const &desc) {

}

string Attachment::getFileName() const {
	string result;

	ptrTable t = dataBase->perform(
		SELECT_ONLY("name").from("attachments").where("id", this->id)
	);

	result = t->get(0, 0);

	return result;
}

string Attachment::getDescription() const {
	string result;

	ptrTable t = dataBase->perform(
		SELECT_ONLY("description").from("attachments").where("id", this->id)
	);

	result = t->get(0, 0);

	return result;
}

IUser*  Attachment::getOwner() const {
	IUser *owner;

	ptrTable t = dataBase->perform(
		SELECT_ONLY("owner_id").from("attachments").where("id", this->id)
	);

	int userId = t->get(0, 0);
	owner = new User(userId);

	return owner;
}
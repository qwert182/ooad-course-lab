#pragma once

#include "Message.h"
#include "dataBase.h"
#include "User.h"

Message::Message(const int id) {
	this->id = id;
}

Message::Message(const class IUser * sender, const class IUser * receiver, const std::string &s, const std::string &t) {
	int senderId = ((User *)sender)->getId();
	int receiverId = ((User *)receiver)->getId();

	static const char * const cols[] = {"sender_id", "receiver_id", "subject", "text"};
	const Element vals[] = {senderId, receiverId, s, t};

	ptrTable table = dataBase->perform(
		Insert().INTO("messages", cols).VALUES(vals)
	);

	this->id = table->get(0, 0);
}

class IUser * Message::getSender() const {
	IUser *result;

	ptrTable t = dataBase->perform(
		SELECT_ONLY("sender_id").from("messages").where("id", this->id)
	);

	int idUser = t->get(0, 0);
	result = new User(idUser);

	return result;
}

class IUser * Message::getReceiver() const {
	IUser *result;

	ptrTable t = dataBase->perform(
		SELECT_ONLY("receiver_id").from("messages").where("id", this->id)
	);

	int idUser = t->get(0, 0);
	result = new User(idUser);

	return result;
}

std::string Message::getSubject() const {
	std::string result;

	ptrTable t = dataBase->perform(
		SELECT_ONLY("subject").from("messages").where("id", this->id)
	);

	result = t->get(0, 0);

	return result;
}

std::string Message::getText() const {
	std::string result;

	ptrTable t = dataBase->perform(
		SELECT_ONLY("text").from("messages").where("id", this->id)
	);

	result = t->get(0, 0);

	return result;
}




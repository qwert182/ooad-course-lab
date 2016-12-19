#pragma once

#include "Mail.h"
#include "Message.h"
#include "dataBase.h"

Mail::Mail(const User *user) {
	this->user = user;
}

void Mail::send(const class IMessage &message) const {

}

std::vector<class IMessage *> Mail::getInBox() const {
	std::vector<class IMessage *> result;

	ptrTable t = dataBase->perform(
		SELECT_ONLY("id").from("messages").where("receiver_id", this->user->getId())
	);

	int numOfMessages = t->getRowCount();
	int id;
	IMessage *message;

	result.reserve(numOfMessages);

	for(int i = 0; i < numOfMessages; i++) {
		id = t->get(i, 0);
		message = new Message(id);
		result.push_back(message);
	}

	return result;
}

std::vector<class IMessage *> Mail::getOutBox() const {
	std::vector<class IMessage *> result;

	ptrTable t = dataBase->perform(
		SELECT_ONLY("id").from("messages").where("sender_id", this->user->getId())
	);

	int numOfMessages = t->getRowCount();
	int id;
	IMessage *message;

	result.reserve(numOfMessages);

	for(int i = 0; i < numOfMessages; i++) {
		id = t->get(i, 0);
		message = new Message(id);
		result.push_back(message);
	}

	return result;
}


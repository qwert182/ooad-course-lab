#pragma once

#include "Mail.h"

Mail::Mail(const IUser &user) {

}

void Mail::send(const class IMessage &message) const {

}

std::vector<class IMessage *> Mail::getInBox() const {
	std::vector<class IMessage *> result;
	return result;
}

std::vector<class IMessage *> Mail::getOutBox() const {
	std::vector<class IMessage *> result;
	return result;
}


#pragma once

#include "Message.h"

Message::Message(const int id) {

}

Message::Message(const class IUser & sender, const std::string &s, const std::string &t) {

}

class IUser * Message::getSender() const {
	IUser * result;
	return result;
}

class IUser * Message::getReceiver() const {
	IUser * result;
	return result;
}

std::string Message::getSubject() const {
	std::string result;
	return result;
}

std::string Message::getText() const {
	std::string result;
	return result;
}


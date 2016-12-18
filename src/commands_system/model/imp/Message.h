#pragma once

#include "../IMessage.h"
#include <vector>

class Message : public IMessage {
private:
	int id;

public:
	virtual class IUser * getSender() const;
	virtual class IUser * getReceiver() const;
	virtual std::string getSubject() const;
	virtual std::string getText() const;

	Message(const int id);
	Message(const class IUser * sender, const class IUser * receiver, const std::string &s, const std::string &t);
	virtual ~Message() {}
};




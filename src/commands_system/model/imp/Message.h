#pragma once

#include "../IMessage.h"
#include <vector>

class Message : public IMessage {
private:
	int id;

public:
	virtual const class IUser & getSender() const;
	virtual const class IUser & getReceiver() const;
	virtual const std::string getSubject() const;
	virtual const std::string getText() const;

	Message(const int id);
	Message(const class IUser & sender, std::string s, std::string t);
	virtual ~Message() {}
};




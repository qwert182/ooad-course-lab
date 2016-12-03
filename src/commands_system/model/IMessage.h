#pragma once

#include <vector>
#include <string>

class IMessage {
public:
	virtual class IUser * getSender() const = 0;
	virtual class IUser * getReceiver() const = 0;
	virtual const std::string & getSubject() const = 0;
	virtual const std::string & getText() const = 0;

	virtual ~IMessage() {}
};



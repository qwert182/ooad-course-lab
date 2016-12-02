#pragma once

#include <vector>

class IMessage {
public:
	virtual const class IUser & getSender() const = 0;
	virtual const class IUser & getReceiver() const = 0;
	virtual const std::string getSubject() const = 0;
	virtual const std::string getText() const = 0;
};



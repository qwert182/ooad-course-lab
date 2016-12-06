#pragma once

#include "../IMail.h"
#include "../IUser.h"
#include "User.h"
#include <vector>

class Mail : public IMail {	
private:
	const User *user;

public:
	virtual void send(const class IMessage &message) const;
	virtual std::vector<class IMessage *> getInBox() const;
	virtual std::vector<class IMessage *> getOutBox() const;

	Mail(const User *user);
	virtual ~Mail() {}
};


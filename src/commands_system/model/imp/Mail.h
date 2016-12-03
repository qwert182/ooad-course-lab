#pragma once

#include "../IMail.h"
#include "../IUser.h"
#include <vector>

class Mail : public IMail {	
private:
	IUser *user;

public:
	virtual void send(const class IMessage &message) const;
	virtual std::vector<class IMessage *> getInBox() const;
	virtual std::vector<class IMessage *> getOutBox() const;

	Mail(const IUser &user);
	virtual ~Mail() {}
};


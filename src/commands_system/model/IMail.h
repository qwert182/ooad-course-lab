#pragma once

#include <vector>
#include <string>

class IMail {
public:
	virtual void send(const class IMessage &message) const = 0;
	virtual std::vector<class IMessage *> getInBox() const = 0;
	virtual std::vector<class IMessage *> getOutBox() const = 0;

	virtual ~IMail() {}
};




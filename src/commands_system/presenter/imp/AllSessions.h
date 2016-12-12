#pragma once

#include "../IAllSessions.h"
#include <vector>

class AllSessions : public IAllSessions {
public:
	virtual class ISession * createSession();
	AllSessions();

private:
	std::vector<class ISession *> a;
};


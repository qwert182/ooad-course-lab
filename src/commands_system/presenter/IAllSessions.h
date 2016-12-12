#pragma once

class IAllSessions {
public:
	virtual class ISession * createSession() = 0;
};


#pragma once

#include "../ISession.h"
#include <string>

class Session : public ISession {
public:
	void logIn(const std::string &login, const std::string &password);
	void signUp(const RegForm &regForm);
	void logOut();
	bool isAuthorized() const;
	Session();
private:
	class IUser *user;
};


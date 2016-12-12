#pragma once

#include <string>
#include "../model/RegForm.h"

class ISession {
public:
	virtual void logIn(const std::string &login, const std::string &password) = 0;
	virtual void signUp(const RegForm &regForm) = 0;
	virtual void logOut() = 0;
	virtual bool isAuthorized() const = 0;
};


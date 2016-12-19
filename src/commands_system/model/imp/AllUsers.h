#pragma once

#include "../IAllUsers.h"
#include <vector>

class AllUsers : public IAllUsers {
public:
	virtual std::vector<class IUser *> getUsers() const;
	virtual class IUser * getUserByLogin(const std::string &login) const;
	virtual void add(const class IUser &user);
	virtual void remove(const class IUser &user);
	virtual class IUser * logIn(const std::string &login, const std::string &password);
	virtual class IUser * signUp(const class RegForm &regForm);

	AllUsers();
	virtual ~AllUsers() {}
};




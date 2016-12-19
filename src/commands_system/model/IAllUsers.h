#pragma once

#include <vector>
#include <string>

class IAllUsers {
public:
	virtual std::vector<class IUser *> getUsers() const = 0;
	virtual class IUser * getUserByLogin(const std::string &login) const = 0;
	virtual void add(const class IUser &user) = 0;
	virtual void remove(const class IUser &user) = 0;
	virtual class IUser * logIn(const std::string &login, const std::string &password) = 0;
	virtual class IUser * signUp(const class RegForm &regForm) = 0;

	virtual ~IAllUsers() {}
};


#pragma once

#include <vector>

class IAllUsers {
public:
	virtual std::vector<class IUser *> getUsers() const = 0;
	virtual void add(const class IUser &user) = 0;
	virtual void remove(const class IUser &user) = 0;
	virtual class IUser & logIn(const class IUser &user) = 0;
	virtual void signUp() = 0;
};


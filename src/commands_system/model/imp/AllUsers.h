#pragma once

#include "../IAllUsers.h"
#include <vector>

class AllUsers : public IAllUsers {
public:
	virtual std::vector<class IUser *> getUsers() const;
	virtual void add(const class IUser &user);
	virtual void remove(const class IUser &user);
	virtual class IUser & logIn(const class IUser &user);
	virtual void signUp();

	AllUsers();
	virtual ~AllUsers() {}
};




#pragma once

#include <vector>
#include <string>

class IUser {
public:
	virtual std::string getName() const = 0;
	virtual void setName(const std::string name) const = 0;

	virtual std::string getLogin() const = 0;
	virtual void setLogin(const std::string login) const = 0;

	virtual std::string getPassword() const = 0;
	virtual void setPassword(const std::string password) const = 0;

	virtual class IUserType * getType() const = 0;
	virtual void setType(const class IUserType &userType) const = 0;

	virtual class IMail * getMail() const = 0;
	virtual class IAllProjects * getProjects() const = 0;

	virtual void logOut() = 0;
};






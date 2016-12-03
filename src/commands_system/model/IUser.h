#pragma once

#include <string>


class IUser {
public:
	virtual std::string getName() const = 0;
	virtual void setName(const std::string &name) = 0;

	virtual std::string getLogin() const = 0;
	virtual void setLogin(const std::string &login) = 0;

	virtual std::string getPassword() const = 0;
	virtual void setPassword(const std::string &password) = 0;

	virtual class IUserType * getType() const = 0;
	virtual void setType(const class IUserType &userType) = 0;

	virtual class IMail * getMail() const = 0;
	virtual class IAllProjects * getProjects() const = 0;

	virtual void logOut() = 0;

	virtual ~IUser() {}
};


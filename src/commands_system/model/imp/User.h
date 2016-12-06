#pragma once

#include "../IUser.h"
#include <vector>

class User : public IUser {
private:
	int id;
	//class IMail *mail;
	//class IAllProjects *projects;

public:
	virtual std::string getName() const;
	virtual void setName(const std::string &name);

	virtual std::string getLogin() const;
	virtual void setLogin(const std::string &login);

	virtual std::string getPassword() const;
	virtual void setPassword(const std::string &password);

	virtual class IUserType * getType() const;
	virtual void setType(const class IUserType &userType);

	virtual class IMail * getMail() const;
	virtual class IAllProjects * getProjects() const;

	virtual void logOut();
	int getId() const;
	

	User(int id);
	User(const std::string &n, const std::string &l, const std::string &p);
	User(const std::string &n, const std::string &l, const std::string &p, const class IUserType &type);

	virtual ~User() {}
};




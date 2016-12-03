#pragma once

#include "../IUser.h"
#include <vector>

class User : public IUser {
private:
	int id;
	class IMail *mail;
	class IAllProjects *projects;

public:
	virtual const std::string & getName() const;
	virtual void setName(const std::string name);

	virtual const std::string & getLogin() const;
	virtual void setLogin(const std::string login);

	virtual const std::string & getPassword() const;
	virtual void setPassword(const std::string password);

	virtual class IUserType * getType() const;
	virtual void setType(const class IUserType &userType);

	virtual class IMail * getMail() const;
	virtual class IAllProjects * getProjects() const;

	virtual void logOut();

	User(int id, const class IMail &m, const class IAllProject &p);
	User(std::string n, std::string l, std::string p);
	User(std::string n, std::string l, std::string p, const class IUserType &type);

	virtual ~User() {}
};




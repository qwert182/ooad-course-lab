#pragma once

#include "../IUserType.h"
#include <vector>

class UserType : public IUserType {
private:
	int id;

public:
	virtual std::string getName() const;
	virtual void setName(const std::string &name);
	virtual bool isManager() const;
	virtual bool isAdmin() const;

	int getId() const;

	UserType(int id);
	UserType(const std::string &name, int type);
	virtual ~UserType() {}
};




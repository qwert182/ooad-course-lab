#pragma once

#include "../IUserType.h"
#include <vector>

class UserType : public IUserType {
private:
	int id;

public:
	virtual const std::string getName() const;
	virtual const void getName(std::string name) const;
	virtual const bool isManager() const;
	virtual const bool isAdmin() const;

	UserType(int id);
	UserType(std::string name, int type);
};




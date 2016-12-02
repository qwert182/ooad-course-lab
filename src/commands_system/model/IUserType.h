#pragma once

#include <vector>

class IUserType {
public:
	virtual const std::string getName() const = 0;
	virtual const void getName(std::string name) const = 0;
	virtual const bool isManager() const = 0;
	virtual const bool isAdmin() const = 0;
};




#pragma once

#include <vector>
#include <string>

class IUserType {
public:
	virtual  std::string getName() const = 0;
	virtual const void getName(std::string name) const = 0;
	virtual bool isManager() const = 0;
	virtual bool isAdmin() const = 0;

	virtual ~IUserType() {}
};




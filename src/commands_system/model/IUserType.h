#pragma once

#include <vector>
#include <string>

class IUserType {
public:
	virtual std::string getName() const = 0;
	virtual void setName(const std::string &name) = 0;
	virtual bool isManager() const = 0;
	virtual bool isAdmin() const = 0;

	virtual ~IUserType() {}
};




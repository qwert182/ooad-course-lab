#pragma once

#include "UserType.h"

UserType::UserType(int id) {
	this->id = id;
}

UserType::UserType(const std::string &name, int type) {

}

std::string UserType::getName() const {
	std::string result;
	return result;
}

void UserType::setName(const std::string &name) {

}

bool UserType::isManager() const {
	bool result;
	return result;
}

bool UserType::isAdmin() const {
	bool result;
	return result;
}


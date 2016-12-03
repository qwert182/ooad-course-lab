#pragma once

#include "User.h"

User::User(int id, const class IMail &m, const class IAllProject &p) {

}

User::User(const std::string &n, const std::string &l, const std::string &p) {

}

User::User(const std::string &n, const std::string &l, const std::string &p, const class IUserType &type) {

}

std::string User::getName() const {
	std::string result;
	return result;
}

void User::setName(const std::string &name) {

}

std::string User::getLogin() const {
	std::string result;
	return result;
}

void User::setLogin(const std::string &login) {

}

std::string User::getPassword() const {
	std::string result;
	return result;
}

void User::setPassword(const std::string &password) {

}

class IUserType * User::getType() const {
	class IUserType * result;
	return result;
}

void User::setType(const class IUserType &userType) {

}

class IMail * User::getMail() const {
	class IMail * result;
	return result;
}

class IAllProjects * User::getProjects() const {
	class IAllProjects * result;
	return result;
}

void User::logOut() {

}
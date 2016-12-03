#pragma once

#include "AllUsers.h"

AllUsers::AllUsers() {

}

std::vector<class IUser *> AllUsers::getUsers() const {
	std::vector<class IUser *> result;
	return result;
}

void AllUsers::add(const class IUser &user) {

}

void AllUsers::remove(const class IUser &user) {

}

class IUser * AllUsers::logIn(const std::string &login, const std::string &password) {
	IUser *result;
	return result;
}

class IUser * AllUsers::signUp(const class RegForm &regForm) {
	IUser *result;
	return result;
}


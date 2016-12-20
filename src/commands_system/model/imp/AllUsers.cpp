#pragma once

#include "AllUsers.h"
#include "dataBase.h"
#include "User.h"
#include "../RegForm.h"
#include "../AccessDeniedException.h"


using std::string;
using std::vector;


AllUsers::AllUsers() {

}

vector<IUser *> AllUsers::getUsers() const {
	vector<class IUser *> result;

	ptrTable t = dataBase->perform(
		SELECT_ONLY("id").from("users")
	);

	int numOfUsers = t->getRowCount();
	int id;
	IUser *user;

	result.reserve(numOfUsers);

	for(int i = 0; i < numOfUsers; i++) {
		id = t->get(i, 0);
		user = new User(id);
		result.push_back(user);
	}

	return result;
}

IUser * AllUsers::getUserByLogin(const string &login) const {
	ptrTable t = dataBase->perform(
		SELECT_ONLY("id").from("users").where("login", login)
	);
	int id = t->get(0, 0);
	return new User(id);
}

void AllUsers::add(const class IUser &user) {

}

void AllUsers::remove(const class IUser &user) {

}

class IUser * AllUsers::logIn(const string &login, const string &password) {
	static const char * const id_password[] = {"id", "password"};
	
	ptrTable t = dataBase->perform(
		SELECT(id_password).from("users").where("login", login)
	);

	if (t->getRowCount() != 1)
		throw AccessDeniedException("such user/login not found");

	int id = t->get(0, 0);
	string db_password = t->get(0, 1);

	if (password != db_password)
		throw AccessDeniedException("wrong password");

	return new User(id);
}

class IUser * AllUsers::signUp(const class RegForm &regForm) {	
	IUser *result = new User(regForm.name, regForm.login, regForm.password);
	return result;
}


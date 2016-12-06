#pragma once

#include "User.h"

#include "../IMail.h"
#include "../IAllProjects.h"


#include "dataBase.h"

#include <memory>



using std::string;
using std::vector;


User::User(int id) {
	this->id = id;
}

User::User(const string &n, const string &l, const string &p) {

}

User::User(const string &n, const string &l, const string &p, const IUserType &type) {

}


string User::getName() const {
	ptrTable t = dataBase->perform(
		SELECT_ONLY("name").from("users").where("id", id)
	);
	return t->get(0, 0);
}

void User::setName(const string &name) {
	
}

string User::getLogin() const {
	ptrTable t = dataBase->perform(
		SELECT_ONLY("login").from("users").where("id", id)
	);
	return t->get(0, 0);
}

void User::setLogin(const string &login) {

}

string User::getPassword() const {
	ptrTable t = dataBase->perform(
		SELECT_ONLY("password").from("users").where("id", id)
	);
	return t->get(0, 0);
}

void User::setPassword(const string &password) {

}

IUserType * User::getType() const {
	IUserType * result;
	return result;
}

void User::setType(const IUserType &userType) {

}

IMail * User::getMail() const {
	IMail * result;
	return result;
}

IAllProjects * User::getProjects() const {
	IAllProjects * result;
	return result;
}

void User::logOut() {

}


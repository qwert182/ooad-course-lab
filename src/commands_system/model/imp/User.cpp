#pragma once

#include "User.h"
#include "Mail.h"
#include "UserType.h"
#include "AllProjects.h"

#include "../IMail.h"
#include "../IAllProjects.h"
#include "../AccessDeniedException.h"

#include "dataBase.h"

#include <memory>

using std::string;
using std::vector;

User::User(int id) {
	this->id = id;
}

User::User(const string &n, const string &l, const string &p) {
	// проверка на уникальность логина
	ptrTable t = dataBase->perform(
		SELECT_ONLY("id").from("users").where("login", l)
	);

	int isUnique = t->getRowCount();
	if(isUnique == 0) {
		static const char * const cols[] = {"name", "login", "password", "type_id"};
		const Element vals[] = {n, l, p, 2};

		ptrTable table = dataBase->perform(
			Insert().INTO("users", cols).VALUES(vals)
		);

		this->id = table->get(0, 0);
	}
	else {
		throw AccessDeniedException("This login already exists! Please, set another login.");
	}
}

User::User(const string &n, const string &l, const string &p, const IUserType &type) {
	// проверка на уникальность логина
	ptrTable t = dataBase->perform(
		SELECT_ONLY("id").from("users").where("login", l)
	);

	int isUnique = t->getRowCount();
	if(isUnique == 0) {
		int typeId = ((UserType &)type).getId();
	
		static const char * const cols[] = {"name", "login", "password", "type_id"};
		const Element vals[] = {n, l, p, typeId};

		ptrTable table = dataBase->perform(
			Insert().INTO("users", cols).VALUES(vals)
		);

		this->id = table->get(0, 0);
	}
	else {
		throw AccessDeniedException("This login already exists! Please, set another login.");
	}
}

string User::getName() const {
	ptrTable t = dataBase->perform(
		SELECT_ONLY("name").from("users").where("id", id)
	);
	return t->get(0, 0);
}

void User::setName(const string &name) {
	dataBase->perform(
		Update("users").SET_ONLY("name", name).where("id", id)
	);
}

string User::getLogin() const {
	ptrTable t = dataBase->perform(
		SELECT_ONLY("login").from("users").where("id", id)
	);
	return t->get(0, 0);
}

void User::setLogin(const string &login) {
	dataBase->perform(
		Update("users").SET_ONLY("login", login).where("id", id)
	);
}

string User::getPassword() const {
	ptrTable t = dataBase->perform(
		SELECT_ONLY("password").from("users").where("id", id)
	);
	return t->get(0, 0);
}

void User::setPassword(const string &password) {
	dataBase->perform(
		Update("users").SET_ONLY("password", password).where("id", id)
	);
}

IUserType * User::getType() const {
	IUserType *result;

	ptrTable t = dataBase->perform(
		SELECT_ONLY("type_id").from("users").where("id", id)
	);

	int idUserType = t->get(0, 0);
	result = new UserType(idUserType);

	return result;
}

void User::setType(const IUserType &userType) {
	int userTypeId = ((UserType &)userType).getId();

	dataBase->perform(
		Update("users").SET_ONLY("type_id", userTypeId).where("id", id)
	);
}

IMail * User::getMail() const {
	IMail *result = new Mail(this);
	return result;
}

IAllProjects * User::getProjects() const {
	return new AllProjects(this);
}

void User::logOut() {

}

int User::getId() const {
	return this->id;
}


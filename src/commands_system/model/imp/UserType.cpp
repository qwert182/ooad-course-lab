#pragma once

#include "UserType.h"
#include "dataBase.h"

UserType::UserType(int id) {
	this->id = id;
}

UserType::UserType(const std::string &name, int type) {
	static const char * const cols[] = {"name", "type"};
	const Element vals[] = {name, type};

	ptrTable table = dataBase->perform(
		Insert().INTO("usertypes", cols).VALUES(vals)
	);

	this->id = table->get(0, 0);
}

std::string UserType::getName() const {
	std::string result;

	ptrTable t = dataBase->perform(
		SELECT_ONLY("name").from("usertypes").where("id", this->id)
	);

	result = t->get(0, 0);

	return result;
}

void UserType::setName(const std::string &name) {
	dataBase->perform(
		Update("usertypes").SET_ONLY("name", name).where("id", id)
	);
}

bool UserType::isManager() const {
	bool result = false;

	ptrTable t = dataBase->perform(
		SELECT_ONLY("type").from("usertypes").where("id", this->id)
	);

	int type = t->get(0, 0);
	if(type == 1) {
		result = true;
	}	

	return result;
}

bool UserType::isAdmin() const {
	bool result = false;

	ptrTable t = dataBase->perform(
		SELECT_ONLY("type").from("usertypes").where("id", this->id)
	);

	int type = t->get(0, 0);
	if(type == 0) {
		result = true;
	}	

	return result;
}

int UserType::getId() const {
	return this->id;
}


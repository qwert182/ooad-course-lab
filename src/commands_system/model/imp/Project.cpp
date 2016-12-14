#pragma once

#include "Project.h"
#include "User.h"
#include "Task.h"
#include "dataBase.h"

using namespace std;

Project::Project(int id) {
	this->id = id;
}

Project::Project(string name, string description) {

}

string Project::getName() const {
	string name;

	ptrTable t = dataBase->perform(
		SELECT_ONLY("name").from("projects").where("id", this->id)
	);

	name = t->get(0, 0);

	return name;
}

void Project::setName(const std::string &name){
	dataBase->perform(
		Update("projects").SET_ONLY("name", name).where("id", id)
	);
}

string Project::getDescription() const {
	string description;

	ptrTable t = dataBase->perform(
		SELECT_ONLY("description").from("projects").where("id", this->id)
	);

	description = t->get(0, 0);

	return description;
}

void Project::setDescription(const std::string &description) {
	dataBase->perform(
		Update("projects").SET_ONLY("description", description).where("id", id)
	);
}

vector<class IUser *> Project::getWorkers() const {
	vector<class IUser *> result;

	ptrTable t = dataBase->perform(
		SELECT_ONLY("user_id").from("project_workers").where("project_id", this->id)
	);

	int numOfUsers = t->getRowCount();
	int idUser;
	IUser *user;

	result.reserve(numOfUsers);

	for(int i = 0; i < numOfUsers; i++) {
		idUser = t->get(i, 0);
		user = new User(idUser);
		result.push_back(user);
	}

	return result;
}

void Project::add(const class IUser &worker) {

}

vector<class ITask *> Project::getTasks() const {
	vector<class ITask *> result;

	ptrTable t = dataBase->perform(
		SELECT_ONLY("id").from("tasks").where("project_id", this->id)
	);

	int numOfTasts = t->getRowCount();
	int idTask;
	ITask *task;

	result.reserve(numOfTasts);

	for(int i = 0; i < numOfTasts; i++) {
		idTask = t->get(i, 0);
		task = new Task(idTask);
		result.push_back(task);
	}

	return result;
}

void Project::add(const class ITask &task) {

}


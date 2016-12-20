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
	static const char * const cols[] = {"name", "description"};
	const Element vals[] = {name, description};

	ptrTable table = dataBase->perform(
		Insert().INTO("projects", cols).VALUES(vals)
	);

	this->id = table->get(0, 0);
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
	static const char * const cols[] = {"user_id", "project_id"};
	const Element vals[] = {((User &)worker).getId(), this->id};

	ptrTable table = dataBase->perform(
		Insert().INTO("project_workers", cols).VALUES(vals)
	);	
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
	// подразумевается, что раз передается параметр Task
	// значит этот task уже записан в таблице tasks
	// следовательно, нужно только определить, к какому проекту она относится

	int taskId = ((Task &)task).getId();

	dataBase->perform(
		Update("tasks").SET_ONLY("project_id", this->id).where("id", taskId)
	);
}


ITask * Project::getTaskByName(const string &name) const {
	ptrTable t = dataBase->perform(
		SELECT_ONLY("id").from("tasks").where("name", name)
	);
	return new Task(t->get(0, 0));
}


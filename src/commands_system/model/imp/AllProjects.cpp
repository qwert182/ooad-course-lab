#pragma once

#include "AllProjects.h"
#include "User.h"
#include "Project.h"
#include "dataBase.h"

using namespace std;

AllProjects::AllProjects(const User *user) {
	this->user = user;
}

IProject * AllProjects::getProjectByName(const std::string &name) const {
	ptrTable t = dataBase->perform(
		SELECT_ONLY("id").from("projects").where("name", name)
	);

	int id = t->get(0, 0);
	return new Project(id);
}


vector<class IProject *> AllProjects::getProjects() const {
	vector<class IProject *> result;

	ptrTable t = dataBase->perform(
		SELECT_ONLY("project_id").from("project_workers").where("user_id", this->user->getId())
	);

	int numOfProjects = t->getRowCount();
	int idProject;
	IProject *project;

	result.reserve(numOfProjects);

	for(int i = 0; i < numOfProjects; i++) {
		idProject = t->get(i, 0);
		project = new Project(idProject);
		result.push_back(project);
	}

	return result;
}

void AllProjects::add(const class IProject &project) {
	// Dont need that
}
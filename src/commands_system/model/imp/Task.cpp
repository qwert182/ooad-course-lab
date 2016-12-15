#pragma once

#include "Task.h"
#include "Note.h"
#include "dataBase.h"

using namespace std;

Task::Task(int id) {
	this->id = id;
}

Task::Task(string name, string theme, string description) {
	// создаем таск, в project_id пишем 0 (или -1)
	// project_id вписать обновлением при создании задачи в проекте

	static const char * const cols[] = {"project_id", "name", "theme", "description"};
	const Element vals[] = {-1, name, theme, description};

	ptrTable table = dataBase->perform(
		Insert().INTO("tasks", cols).VALUES(vals)
	);

	this->id = table->get(0, 0);
}

string Task::getName() const {
	string name;

	ptrTable t = dataBase->perform(
		SELECT_ONLY("name").from("tasks").where("id", this->id)
	);

	name = t->get(0, 0);

	return name;
}

void Task::setName(const std::string &name) {
	dataBase->perform(
		Update("tasks").SET_ONLY("name", name).where("id", id)
	);
}

string Task::getTheme() const {
	string theme;

	ptrTable t = dataBase->perform(
		SELECT_ONLY("theme").from("tasks").where("id", this->id)
	);

	theme = t->get(0, 0);

	return theme;
}

void Task::setTheme(const std::string &theme) {
	dataBase->perform(
		Update("tasks").SET_ONLY("theme", theme).where("id", id)
	);
}

string Task::getDescription() const {
	string description;

	ptrTable t = dataBase->perform(
		SELECT_ONLY("description").from("tasks").where("id", this->id)
	);

	description = t->get(0, 0);

	return description;
}

void Task::setDescription(const std::string &description) {
	dataBase->perform(
		Update("tasks").SET_ONLY("description", description).where("id", id)
	);
}

vector<class INote *> Task::getNotes() const {
	vector<class INote *> result;

	ptrTable t = dataBase->perform(
		SELECT_ONLY("id").from("notes").where("task_id", this->id)
	);

	int numOfNotes = t->getRowCount();
	int idNote;
	INote *note;

	result.reserve(numOfNotes);

	for(int i = 0; i < numOfNotes; i++) {
		idNote = t->get(i, 0);
		note = new Note(idNote);
		result.push_back(note);
	}

	return result;
}

void Task::add(const class INote &note) {
	int noteId = ((Note &)note).getId();

	dataBase->perform(
		Update("notes").SET_ONLY("task_id", this->id).where("id", noteId)
	);
}

vector<class IAttachment *> Task::getAttachments() const {
	vector<class IAttachment *> result;

	vector<class INote *> notes = this->getNotes();

	int numOfNotes = notes.size();
	for(int i = 0; i < numOfNotes; i++) {
		
		vector<class IAttachment *> attach = notes[i]->getAttachments();
		result.insert(result.end(), attach.begin(), attach.end());
	}

	return result;
}

void Task::add(const class IAttachment &attachments) {
	
}

int Task::getId() const {
	return this->id;
}
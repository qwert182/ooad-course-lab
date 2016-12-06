#include "AllProjects.h"
using namespace std;

AllProjects::AllProjects(User *user) {
	this->user = user;
}

vector<class IProject *> AllProjects::getProjects() const {
	vector<class IProject *> result;
	return result;
}

void AllProjects::add(const class IProject &project) {

}
#include "Session.h"
#include <string>
#include "../../model/IAllUsers.h"
#include "../../model/IUser.h"

extern IAllUsers *allUsers;
IAllUsers *allUsers = nullptr;

using namespace std;



Session::Session() {
	user = nullptr;
}

void Session::logIn(const string &login, const string &password) {
	this->user = allUsers->logIn(login, password);
}

void Session::signUp(const RegForm &regForm) {
	this->user = allUsers->signUp(regForm);
}

void Session::logOut() {
	user->logOut();
	delete user;
}

bool Session::isAuthorized() const {
	return user != nullptr;
}


#include "allUsersInstance.h"

#include "../../model/imp/AllUsers.h"

IAllUsers *allUsers;

void allUsers_Create() {
	allUsers = new AllUsers();
}


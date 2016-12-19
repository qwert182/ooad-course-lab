#include "UsersResource.h"

#include "../../model/IAllUsers.h"
#include "allUsersInstance.h"

#include "utils/response.h"
#include "utils/status.h"
#include "utils/append.h"

#include "BadRequestException.h"


using std::vector;
using std::string;


UsersResource::UsersResource() {
}



vector<char> UsersResource::post(const vector<char> &content, Session *session) const {
	must_be_authorized(session);

  string active(content.begin(), content.end());
	if (active != "active") {
		throw BadRequestException("non active /projects");
	}

  vector<char> result = getStatusBy(200);
	appendCRLF(result);

  vector<IUser *> users = allUsers->getUsers();
  size_t i, count = users.size();

	for (i = 0; i < count; ++i) {
	  IUser *user = users[i];
		append(result, "<option>");
		append(result, user->getLogin());
		append(result, "</option>");
		delete user;
	}

	return result;
}


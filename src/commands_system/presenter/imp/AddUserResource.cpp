#include "AddUserResource.h"

#include "BadRequestException.h"

#include "utils/parse_post.h"
#include "utils/status.h"
#include "utils/append.h"
#include "utils/read_file.h"
#include "utils/response.h"

#include "allUsersInstance.h"
#include "../../model/IProject.h"
#include "../../model/IAllProjects.h"
#include "../../model/AccessDeniedException.h"


using std::vector;
using std::string;
using std::unordered_map;
using std::make_pair;
using std::unique_ptr;


AddUserResource::AddUserResource() {}












vector<char> AddUserResource::post(const vector<char> &content, Session *session) const {
	must_be_authorized(session);

  unordered_map<string, string> login_and_password = parse_post(string(content.begin(), content.end()));
  const string
	  &user_login = getValueByKey(login_and_password, "user"),
	  &project = getValueByKey(login_and_password, "project");

	if (!isFlagSet(login_and_password, "active")) {
	  vector<char> result = getStatusBy(400);
		appendCRLF(result);
		append(result, "only active page supported (please enable javascript)");
		return result;
	}

	try {
	  unique_ptr<IUser> user ( allUsers->getUserByLogin(user_login) );
	  unique_ptr<IAllProjects> allprjs ( user->getProjects() );
	  unique_ptr<IProject> project ( allprjs->getProjectByName(project) );

		project->add(*user);
	} catch (const AccessDeniedException &) {
	  vector<char> result = getStatusBy(403);
		appendCRLF(result);
		append(result, "access denied");
		return result;
	} catch (const Exception &e) {
	  vector<char> result = getStatusBy(500);
		appendCRLF(result);
		append(result, e.what());
		return result;
	}


  vector<char> result = getStatusBy(200);
	appendCRLF(result);
	return result;
}

	
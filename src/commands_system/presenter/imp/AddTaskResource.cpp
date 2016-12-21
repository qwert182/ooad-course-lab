#include "AddTaskResource.h"

#include "BadRequestException.h"

#include "utils/parse_post.h"
#include "utils/status.h"
#include "utils/append.h"
#include "utils/read_file.h"
#include "utils/response.h"

#include "allUsersInstance.h"
#include "../../model/imp/Project.h"
#include "../../model/AccessDeniedException.h"


using std::vector;
using std::string;
using std::unordered_map;
using std::make_pair;
using std::unique_ptr;


AddTaskResource::AddTaskResource() {}




vector<char> AddTaskResource::get(Session *session) const {

	return file_response_must_be_authorized("html/addproject.htm", session);
}










vector<char> AddTaskResource::post(const vector<char> &content, Session *session) const {
	must_be_authorized(session);

  unordered_map<string, string> login_and_password = parse_post(string(content.begin(), content.end()));
  /*const string
	  &name = getValueByKey(login_and_password, "name"),
	  &description = getValueByKey(login_and_password, "description");

	if (!isFlagSet(login_and_password, "active")) {
	  vector<char> result = getStatusBy(400);
		appendCRLF(result);
		append(result, "only active page supported (please enable javascript)");
		return result;
	}

  IUser *user = session->getUser();
	try {
	  unique_ptr<IProject> project(  new Project(name, description)  );
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
	}*/


  vector<char> result = getStatusBy(200);
	appendCRLF(result);
	append(result, "/projects");
	return result;
}


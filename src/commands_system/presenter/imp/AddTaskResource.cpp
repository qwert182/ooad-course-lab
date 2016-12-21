#include "AddTaskResource.h"

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
#include "../../model/imp/Task.h"


using std::vector;
using std::string;
using std::unordered_map;
using std::make_pair;
using std::unique_ptr;


AddTaskResource::AddTaskResource() {}













vector<char> AddTaskResource::post(const vector<char> &content, Session *session) const {
	must_be_authorized(session);

  unordered_map<string, string> login_and_password = parse_post(string(content.begin(), content.end()));
  const string
	  &task_name = getValueByKey(login_and_password, "name"),
	  &task_theme = getValueByKey(login_and_password, "theme"),
	  &task_description = getValueByKey(login_and_password, "description"),
	  &project = getValueByKey(login_and_password, "project");

	if (!isFlagSet(login_and_password, "active")) {
	  vector<char> result = getStatusBy(400);
		appendCRLF(result);
		append(result, "only active page supported (please enable javascript)");
		return result;
	}

	try {
	  IUser * user = session->getUser();
	  unique_ptr<IAllProjects> allprjs ( user->getProjects() );
	  unique_ptr<IProject> project ( allprjs->getProjectByName(project) );
	  unique_ptr<ITask> task ( new Task(task_name, task_theme, task_description) );

		project->add(*task);
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


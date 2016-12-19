#include "OneProjectResource.h"

#include "../../model/IAllProjects.h"
#include "../../model/IProject.h"
#include "../../model/ITask.h"

#include "utils/response.h"
#include "utils/status.h"
#include "utils/append.h"
#include "utils/parse_post.h"

#include "BadRequestException.h"

#include <memory>

using std::vector;
using std::string;
using std::unordered_map;
using std::unique_ptr;


OneProjectResource::OneProjectResource() {
}




vector<char> OneProjectResource::get(Session *session) const {
	return file_response_must_be_authorized("html/project.htm", session);
}



vector<char> OneProjectResource::post(const vector<char> &content, Session *session) const {
	must_be_authorized(session);

  unordered_map<string, string> what_content = parse_post(string(content.begin(), content.end()));

  const string
	  &project_name = getValueByKey(what_content, "project"),
	  &what = getValueByKey(what_content, "content");

  vector<char> result = getStatusBy(200);
	append(result, "Content-Type: text/html;charset=windows-1251\r\n");
	appendCRLF(result);

  const IUser *user = session->getUser();
  unique_ptr<const IAllProjects> projects(  user->getProjects()  );
  unique_ptr<const IProject> project(  projects->getProjectByName(project_name)  );

	if (what == "project_description") {
		append(result, project->getDescription());
	} else if (what == "task_list") {
	  vector<ITask *> tasks = project->getTasks();
		for (size_t i = 0; i < tasks.size(); ++i) {
		  ITask *task = tasks[i];
			append(result, "<li>");
			append(result, "<a href=\"");
			append(result, project_name + '/' + task->getName());
			append(result, "\">");
			append(result, task->getDescription());
			append(result, "</a>");
			append(result, "</li>");
			delete task;
		}
	} else if (what == "workers_list") {
	  vector<IUser *> workers = project->getWorkers();
		for (size_t i = 0; i < workers.size(); ++i) {
		  IUser *worker = workers[i];
			append(result, "<li>");
			append(result, worker->getName());
			append(result, "</li>");
			delete worker;
		}
	} else {
		throw BadRequestException("non active /projects");
	}

	return result;
}


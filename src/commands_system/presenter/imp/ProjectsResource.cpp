#include "ProjectsResource.h"

#include "../../model/IAllProjects.h"
#include "../../model/IProject.h"

#include "utils/response.h"
#include "utils/status.h"
#include "utils/append.h"

#include "BadRequestException.h"


using std::vector;
using std::string;


ProjectsResource::ProjectsResource() {
}


vector<char> ProjectsResource::get(Session *session) const {
	return file_response_must_be_authorized("html/projects.htm", session);
}


vector<char> ProjectsResource::post(const vector<char> &content, Session *session) const {
  string active(content.begin(), content.end());
	if (active != "active") {
		throw BadRequestException("non active /projects");
	}


  vector<char> result = getStatusBy(200);
	appendCRLF(result);

  IUser *user = session->getUser();
  IAllProjects *allProjects = user->getProjects();
  vector<IProject *> projects = allProjects->getProjects();
  size_t i, count = projects.size();

	for (i = 0; i < count; ++i) {
	  IProject *project = projects[i];
		append(result, project->getName());
		appendCRLF(result);
		delete project;
	}

	delete allProjects;

	return result;
}


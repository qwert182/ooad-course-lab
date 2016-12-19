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
	must_be_authorized(session);

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
		append(result, "<li>");
		append(result, "<a href=\"");
		append(result, "/projects/" + project->getName());
		append(result, "\">");
		append(result, project->getDescription());
		append(result, "</a>");
		append(result, "</li>");
		delete project;
	}

	delete allProjects;

	return result;
}


#include "IResource.h"

#include "StaticFileResource.h"
#include "LoginActionResource.h"
#include "MainPageResource.h"
#include "ProjectsResource.h"
#include "MessagesResource.h"
#include "UsersResource.h"
#include "SendResource.h"
#include "OneProjectResource.h"
#include "OneTaskResource.h"
#include "RegformResource.h"

#include "utils/request.h"
#include "utils/append.h"

#include <string>
#include <unordered_map>

#include "NotFoundException.h"
#include "NotImplementedException.h"
#include "SessionException.h"



using std::string;
using std::unordered_map;
using std::make_pair;
using std::vector;





typedef unordered_map<string, IResource*> r_map;
static r_map *resources;


void IResource::Init() {
	r_map *all = resources = new r_map();
	all->insert(make_pair("/", new MainPageResource()));
	all->insert(make_pair("/login", new LoginActionResource()));
	all->insert(make_pair("/login.css", new StaticFileResource("html/login.css")));
	all->insert(make_pair("/login.js", new StaticFileResource("html/login.js")));

	all->insert(make_pair("/projects", new ProjectsResource()));
	all->insert(make_pair("/projects.js", new StaticFileResource("html/projects.js")));
	
	all->insert(make_pair("/messages", new MessagesResource()));
	all->insert(make_pair("/messages.js", new StaticFileResource("html/messages.js")));
	all->insert(make_pair("/messages.css", new StaticFileResource("html/messages.css")));
	
	all->insert(make_pair("/users", new UsersResource()));
	all->insert(make_pair("/send", new SendResource()));
	
	all->insert(make_pair("/projects/", new OneProjectResource()));
	all->insert(make_pair("/project.js", new StaticFileResource("html/project.js")));
	
	all->insert(make_pair("/projects/*/task/", new OneTaskResource()));
	all->insert(make_pair("/task.js", new StaticFileResource("html/task.js")));
	all->insert(make_pair("/regform", new RegformResource()));
	all->insert(make_pair("/regform.js", new StaticFileResource("html/login.js")));


	all->insert(make_pair("/forall.css", new StaticFileResource("html/forall.css")));
}




void IResource::Dispose() {
  r_map *all = resources;
  r_map::iterator it;

	for (it = all->begin(); it != all->end(); ++it) {
		delete it->second;
	}

	delete resources;
}



vector<char> IResource::notImplemented() {
	throw NotImplementedException("IResource::notImplemented()");
}





std::vector<char> IResource::perform(const Request &request) {
  r_map *all = resources;
  r_map::const_iterator found;
  const vector<char> *post_content = nullptr;
  vector<char> projects_content;

  const string prjs = "/projects/";
	if (request.path.substr(0, prjs.length()) == prjs) {
	  string prj = request.path.substr(prjs.length());
	  size_t found_task = prj.find('/');
		if (found_task != string::npos) {
		  const string task = prj.substr(found_task + 1);
			prj.erase(found_task);
			if (request.type == "POST") {
				append(projects_content, "task=" + task);
				appendCRLF(projects_content);
				append(projects_content, "project=" + prj);
				appendCRLF(projects_content);
				append(projects_content, "content=");
				append(projects_content, request.content);
				post_content = &projects_content;
			}
			found = all->find("/projects/*/task/");
		} else {
			if (request.type == "POST") {
				append(projects_content, "project=" + prj);
				appendCRLF(projects_content);
				append(projects_content, "content=");
				append(projects_content, request.content);
				post_content = &projects_content;
			}
			found = all->find(prjs);
		}
	} else {
		found = all->find(request.path);
		post_content = &request.content;
	}


	if (found == all->end())
		throw NotFoundException(request.path);

  IResource *res = found->second;

  auto cookie_found = request.headers.find("Cookie");
  Session *session = nullptr;

	if (cookie_found != request.headers.end()) {
		try {
			session = Session::GetExisting(cookie_found->second);
		} catch (const SessionException &) {
		}
	}

	if (request.type == "GET")
		return res->get(session);
	else if (request.type == "POST")
		return res->post(*post_content, session);
	else
		throw NotImplementedException("unknown request type");
}


#include "IResource.h"

#include "StaticFileResource.h"
#include "LoginActionResource.h"
#include "MainPageResource.h"
#include "utils/request.h"

#include <string>
#include <unordered_map>

#include "NotFoundException.h"
#include "NotImplementedException.h"


#include "Session.h"
#include "SessionException.h"



using std::string;
using std::unordered_map;
using std::make_pair;
using std::vector;





typedef unordered_map<string, IResource*> r_map;
static r_map *resources;


void IResource::init() {
	r_map *all = resources = new r_map();
	all->insert(make_pair("/", new MainPageResource()));
	all->insert(make_pair("/login", new LoginActionResource()));
	all->insert(make_pair("/login.css", new StaticFileResource("html/login.css")));
	all->insert(make_pair("/login.js", new StaticFileResource("html/login.js")));
}




void IResource::dispose() {
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



//static
//ISession * getSessionBy(const Request &request) {
	//auto &h = request.headers;
	//h.find("");
//	return allSessions->createSession();
//}




std::vector<char> IResource::perform(const Request &request) {
  r_map *all = resources;
  r_map::const_iterator found = all->find(request.path);

	if (found == all->end())
		throw NotFoundException(request.path);

  IResource *res = found->second;
  //ISession *session = getSessionBy(request);

  auto cookie_found = request.headers.find("Cookie");
	if (cookie_found != request.headers.end()) {
	  Session *session;
		try {
			session = Session::GetExisting(cookie_found->second);
		} catch (const SessionException
	}

	if (request.type == "GET")
		return res->get();
	else if (request.type == "POST")
		return res->post(request.content);
	else
		throw NotImplementedException("unknown request type");
}


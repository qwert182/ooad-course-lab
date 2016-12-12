#include "IResource.h"

#include "StaticFileResource.h"
#include "LoginActionResource.h"
#include "request.h"

#include <string>
#include <unordered_map>

#include "NotFoundException.h"
#include "NotImplementedException.h"

using std::string;
using std::unordered_map;
using std::make_pair;

typedef unordered_map<string, IResource*> r_map;
static r_map *resources;


void IResource::notImplemented() {
	throw NotImplementedException("IResource::notImplemented()");
}


void IResource::init() {
	r_map *all = resources = new r_map();
	all->insert(make_pair("/", new StaticFileResource("html/login.htm")));
	all->insert(make_pair("/main.css", new StaticFileResource("html/main.css")));
	all->insert(make_pair("/login", new LoginActionResource()));
}


void IResource::dispose() {
  r_map *all = resources;
  r_map::iterator it;

	for (it = all->begin(); it != all->end(); ++it) {
		delete it->second;
	}

	delete resources;
}



void IResource::perform(const Request &request, SOCKET a) {
  r_map *all = resources;
  r_map::const_iterator found = all->find(request.path);

	if (found == all->end())
		throw NotFoundException(request.path);

  IResource *res = found->second;

	if (request.type == "GET")
		res->get(a);
	else if (request.type == "POST")
		res->post(a, request.content);
	else
		throw NotImplementedException("unknown request type");

}


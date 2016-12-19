#include "Session.h"

#include <sstream>
#include <stdlib.h>
#include "utils/parse_cookie.h"
#include "SessionException.h"

using std::string;
using std::unordered_map;
using std::make_pair;
using std::istringstream;
using std::ostringstream;


IUser * Session::getUser() const {
	return this->user;
}

string Session::getId() const {
  ostringstream oss;
	oss << this->id;
	return oss.str();
}



Session::Session(IUser *user) {
	do {
		this->id = rand();
	} while (all->find(this->id) != all->end());

	this->user = user;
	all->insert(make_pair(this->id, this));
}


Session::~Session() {
	delete this->user;
}



Session * Session::GetExisting(const std::string &cookie) {
  unordered_map<string, string> map = parse_cookie(cookie);
  auto found_sid = map.find("sid");
	if (found_sid == map.end())
		throw SessionException("can't get existing session: no sid cookie");

  istringstream id_s(found_sid->second);
  int id;
	id_s >> id;
	if (id_s.bad() || !id_s.eof())
		throw SessionException("can't get existing session: bad sid cookie");

  auto found = all->find(id);
	if (found == all->end())
		throw SessionException("can't get existing session: session with such sid doesn't exist");

	return found->second;
}



unordered_map<int, Session *> *Session::all;


void Session::InitAll() {
	all = new unordered_map<int, Session *>();
}


void Session::DisposeAll() {
	for (auto it = all->begin(), end = all->end(); it != end; ++it) {
		delete it->second;
	}
	delete all;
}


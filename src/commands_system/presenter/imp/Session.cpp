#include "Session.h"

#include <sstream>
#include <stdlib.h>
#include "utils/parse_cookie.h"
#include "SessionException.h"

using std::string;
using std::unordered_map;
using std::make_pair;
using std::istringstream;


IUser * Session::getUser() const {
	return this->user;
}


Session::Session(IUser *user) {
	do {
		this->id = rand();
	} while (all.find(this->id) != all.end());

	this->user = user;
	all.insert(make_pair(this->id, this));
}


Session * Session::GetExisting(const std::string &cookie) {
  unordered_map<string, string> map = parse_cookie(cookie);
  auto found_sid = map.find("sid");
	if (found_sid == map.end())
		throw SessionException("can't get existing session: no sid cookie");

  istringstream id_s(found_sid->second);
  int id;
	id_s >> id;
	if (!id_s.good() || !id_s.eof())
		throw SessionException("can't get existing session: bad sid cookie");

  auto found = all.find(id);
	if (found == all.end())
		throw SessionException("can't get existing session: session with such sid doesn't exist");

	return found->second;
}

std::unordered_map<int, Session *> Session::all;


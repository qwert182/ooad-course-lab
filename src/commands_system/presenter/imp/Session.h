#pragma once

#include <string>
#include <unordered_map>

#include "../../model/IUser.h"

class Session {
private:
	IUser *user;
	int id;

	Session(const Session &);
	void operator =(const Session &);

	static std::unordered_map<int, Session *> all;
public:
	int getId() const;
	IUser * getUser() const;
	Session(IUser *user);

	static Session * GetExisting(const std::string &cookie);
};


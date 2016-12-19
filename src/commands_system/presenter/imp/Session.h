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

	~Session();

	static std::unordered_map<int, Session *> *all;
public:
	std::string getId() const;
	IUser * getUser() const;
	Session(IUser *user);

	static Session * GetExisting(const std::string &cookie);
	static void InitAll();
	static void DisposeAll();
};


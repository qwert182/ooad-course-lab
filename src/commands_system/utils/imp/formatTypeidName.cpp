#pragma once

#include "../formatTypeidName.h"

using std::string;

string formatTypeidName(const string &name) {
  size_t i;
	if ((i = name.find_first_of(' ')) != string::npos) {
		return name.substr(i+1);
	}
	return name;
}


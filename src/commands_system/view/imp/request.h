#pragma once

#include <string>
#include <map>
#include <vector>

#include <winsock.h>


struct Request {
	std::string
		type,
		path,
		version,
		all;

	std::map<std::string, std::string>
		headers;

	std::vector<char>
		content;

	void set_headers(const std::string &all);
	void correct_path();
	void set_09(const std::string &line, size_t sp);
	void set_10(const std::string &all, size_t sp_first, size_t sp_last);
	Request(const std::string &line, int version, int sp_first, int sp_last);


	static Request receive(SOCKET a);
};


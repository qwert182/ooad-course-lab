#include "LoginActionResource.h"

#include <string>
#include <unordered_map>
#include "BadRequestException.h"


using std::vector;
using std::string;
using std::unordered_map;
using std::make_pair;


LoginActionResource::LoginActionResource() {}


#define GTEIFNF(x) if ((x) == string::npos) goto err



static
unordered_map<string, string> parse(const string &str) {
  unordered_map<string, string> result;
  size_t enter_pos, equal_sign_pos;
	GTEIFNF(equal_sign_pos = str.find('='));
	GTEIFNF(enter_pos = str.find("\r\n"));

	result.insert(make_pair(
		str.substr(0, equal_sign_pos),
		str.substr(equal_sign_pos + 1, enter_pos - equal_sign_pos - 1)
	));

	GTEIFNF(equal_sign_pos = str.find('=', enter_pos));
	result.insert(make_pair(
		str.substr(enter_pos + 2, equal_sign_pos - enter_pos - 2),
		str.substr(equal_sign_pos + 1)
	));

	return result;
err:
	throw BadRequestException("when parse POST data (bad login and password)");
}


void LoginActionResource::post(SOCKET a, const vector<char> &content) const {
  unordered_map<string, string> login_and_password = parse(string(content.begin(), content.end()));
  string &login = login_and_password.at("login");
  string &password = login_and_password.at("password");
	//IUser *user = allUsers.logIn(login, password)
}


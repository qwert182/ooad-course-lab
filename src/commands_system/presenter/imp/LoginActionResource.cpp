#include "LoginActionResource.h"

#include "BadRequestException.h"

#include "utils/parse_post.h"
#include "utils/status.h"
#include "utils/append.h"
#include "utils/read_file.h"

using std::vector;
using std::string;
using std::unordered_map;
using std::make_pair;


LoginActionResource::LoginActionResource() {}


/*#include <algorithm>
using std::search;

void replace(vector<char> &data, const string &what, const string &to) {
  vector<char>::iterator start = data.begin();
  vector<char>::iterator found = search(start, data.end(), what.begin(), what.end());
	data.erase(found, found + what.size());
	data.insert(found, to.begin(), to.end());
}*/


vector<char> LoginActionResource::get() const {
  /*vector<char> result = getStatusBy(200);
	appendCRLF(result);
  vector<char> file = read_file("html/login.htm");
	replace(file, "[TEMPLATE_CLASS_ERRMSG]", "hidden_errmsg");*/
  
	//search(file.begin(), file.end(), );
	//send_response(a, 200);
	//send_file(a, "html/login.htm");
  vector<char> result = getStatusBy(200);
	appendCRLF(result);
	append(result, read_file("html/login.htm"));
	return result;
}


static
const string & getValueByKey(const unordered_map<string, string> &map, const string &key) {
  auto found = map.find(key);
	if (found == map.end())
		throw BadRequestException("in getValueByKey in LoginActionResource");
	return found->second;
}

static
bool isFlagSet(const unordered_map<string, string> &map, const string &flag) {
  auto found = map.find(flag);
	if (found == map.end())
		return false;
  const string &value = found->second;
	return value.length() == 0;
}

vector<char> LoginActionResource::post(const vector<char> &content) const {
  unordered_map<string, string> login_and_password = parse_post(string(content.begin(), content.end()));
  const string
	  &login = getValueByKey(login_and_password, "login"),
	  &password = getValueByKey(login_and_password, "password");

	if (!isFlagSet(login_and_password, "active")) {
	  vector<char> result = getStatusBy(400);
		appendCRLF(result);
		append(result, "only active login page supported (please enable javascript)");
		return result;
	}

	if (true) { // bad login password
	  vector<char> result = getStatusBy(200);
		appendCRLF(result);
		append(result, "bad");
		return result;
	}
	//IUser *user = allUsers.logIn(login, password)

  vector<char> result = getStatusBy(303);
	append(result, "Location: /\r\n");
	append(result, "Set: /\r\n");
	appendCRLF(result);
	return result;
}


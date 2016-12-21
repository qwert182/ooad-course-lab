#include "RegformResource.h"

#include "BadRequestException.h"

#include "utils/parse_post.h"
#include "utils/status.h"
#include "utils/append.h"
#include "utils/read_file.h"

#include "allUsersInstance.h"
#include "../../model/IUser.h"
#include "../../model/AccessDeniedException.h"
#include "../../model/RegForm.h"

using std::vector;
using std::string;
using std::unordered_map;
using std::make_pair;


RegformResource::RegformResource() {}




vector<char> RegformResource::get(Session *) const {
  vector<char> result = getStatusBy(200);
	appendCRLF(result);
	append(result, read_file("html/regform.htm"));
	return result;
}










vector<char> RegformResource::post(const vector<char> &content, Session *session) const {
  unordered_map<string, string> login_and_password = parse_post(string(content.begin(), content.end()));
  const string
	  &name = getValueByKey(login_and_password, "name"),
	  &login = getValueByKey(login_and_password, "login"),
	  &password = getValueByKey(login_and_password, "password");

	if (!isFlagSet(login_and_password, "active")) {
	  vector<char> result = getStatusBy(400);
		appendCRLF(result);
		append(result, "only active regform page supported (please enable javascript)");
		return result;
	}

	if (session != nullptr) {
	  vector<char> result = getStatusBy(400);
		appendCRLF(result);
		append(result, "you are already logged in");
		return result;
	}


  IUser *user = nullptr;
	try {
	  RegForm regform;
		regform.name = name;
		regform.login = login;
		regform.password = password;
		user = allUsers->signUp(regform);
	} catch (const AccessDeniedException &) {
	  vector<char> result = getStatusBy(403);
		appendCRLF(result);
		append(result, "access denied");
		return result;
	} catch (const Exception &e) {
	  vector<char> result = getStatusBy(500);
		appendCRLF(result);
		append(result, e.what());
		return result;
	}


  Session *new_session = new Session(user);
  string sid = new_session->getId();


  vector<char> result = getStatusBy(200);
	appendCRLF(result);

	append(result, sid);
	appendCRLF(result);
	append(result, "/");
	appendCRLF(result);
	return result;
}


#include "parse_post.h"


#include <sstream>

#include "../BadRequestException.h"


using std::string;
using std::unordered_map;
using std::istringstream;
using std::getline;
using std::make_pair;


unordered_map<string, string> parse_post(const string &str) {
  unordered_map<string, string> res;
  istringstream ss(str);
  string line;

	while (!ss.eof()) {
		getline(ss, line);
		if (line.length() != 0) {
			if (line.back() == '\r') line.erase(line.end() - 1);

		  size_t eq = line.find('=');
			if (eq != string::npos) {
				res.insert(make_pair(line.substr(0, eq), line.substr(eq + 1)));
			} else {
				res.insert(make_pair(line, ""));
			}
		}
	}


	return res;
}


bool isFlagSet(const unordered_map<string, string> &map, const string &flag) {
  auto found = map.find(flag);
	if (found == map.end())
		return false;
  const string &value = found->second;
	return value.length() == 0;
}



const string & getValueByKey(const unordered_map<string, string> &map, const string &key) {
  auto found = map.find(key);
	if (found == map.end())
		throw BadRequestException("in getValueByKey in LoginActionResource");
	return found->second;
}


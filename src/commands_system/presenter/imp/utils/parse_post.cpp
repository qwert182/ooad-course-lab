#include "parse_post.h"


#include <sstream>


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


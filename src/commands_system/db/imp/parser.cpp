#include "parser.h"
#include "ParseFailedException.h"

#include <sstream>

using namespace std;



static
void replace_char_codes(string &word){
  size_t found;
	while ((found = word.find("\\x20")) != string::npos)
		word.replace(found, 4, " ");
}



static
vector<string> split(const string &line){
  string word;

  istringstream iss = istringstream(line);
  vector <string> split_line;

	while (!iss.eof()) {
		iss >> word;
		replace_char_codes(word);
		split_line.push_back(word);
	}

	return split_line;
}



static
TableWithHeader parse_TableWithHeader(const vector<vector<string>> &parsed_table) {
	//Input: {{int, string},
	//		  {id, name},
	//		  {key, -},
	//		  {1, text\x20blabla}}		// с 3-ей строчки
	//Output:
	//content {{1, text\x20blabla}}		// остальное-системна€ инфа ненужна€
  size_t i, j;
  vector<vector<Element>> content;


	if (parsed_table.size() < 3)
		throw ParseFailedException("Table must contain header");

	content.resize(parsed_table.size() - 3);

	for (i = 3; i < parsed_table.size(); ++i) {
		content[i-3].reserve(parsed_table[0].size());

		for (j = 0; j < parsed_table[0].size(); ++j) {

			if (parsed_table[0][j] == "int") {
			  istringstream convert(parsed_table[i][j]);
			  int x;
				convert >> x;

				bool g = !convert.bad() && convert.eof();
				if (!g) {
					throw ParseFailedException("can't convert \"" + parsed_table[i][j] + '"');
				}
				content[i-3].push_back(x);
			} else if (parsed_table[0][j] == "string") {
				content[i-3].push_back(parsed_table[i][j]);
			} else {
				throw ParseFailedException("unknown type");
			}
		}

	}

  TableWithHeader t;
	t.types = parsed_table[0];
	t.hat = parsed_table[1];
	t.links = parsed_table[2];
	t.content = content;
	return t;
}




TableWithHeader parse(istream &file) {
	if (!file.good())
		throw ParseFailedException("file not opened for parse");

  string line;
  vector<vector<string>> a;


	while (!file.eof()) {
		getline(file, line);
		a.push_back(split(line));
	}

	file.clear();                 // clear fail and eof bits
	file.seekg(0, ios::beg); 

	return parse_TableWithHeader(a);
}



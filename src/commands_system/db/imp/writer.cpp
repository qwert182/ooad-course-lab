#include "writer.h"
#include "WriteFailedException.h"

using std::ostream;
using std::vector;
using std::string;
using std::ios;




static void write_line(const vector<string> &line, ostream &file) {
	file << line[0];
	for (size_t i = 1; i < line.size(); ++i) {
		file << '\t' << line[i];
	}
	file << '\n';
}


typedef void (*write_f)(const Element &, ostream &);

static void write_element_line(const vector<Element> &line, const vector<write_f> &write, ostream &file) {
	write[0](line[0], file);
	for (size_t i = 1; i < line.size(); ++i) {
		file << '\t';
		write[i](line[i], file);
	}
}



static void int_writer(const Element &integer, ostream &file) {
	file << (int)integer;
}

static
void replace_char_codes(string &word){
  size_t found;
	while ((found = word.find(" ")) != string::npos)
		word.replace(found, 1, "\\x20");
}

static void string_writer(const Element &str, ostream &file) {
	string tmp = (string)str;
	replace_char_codes(tmp);
	file << tmp;
}


static vector<write_f> createWriters(const vector<string> &hat) {
	vector<write_f> result(hat.size());
	for (size_t i = 0; i < hat.size(); ++i) {
		if (hat[i] == "int") result[i] = int_writer;
		else if (hat[i] == "string") result[i] = string_writer;
		else
			throw WriteFailedException("unknown type");
	}
	return result;
}



void write(const TableWithHeader &t, ostream &file) {
	if (!file.good())
		throw WriteFailedException("file not opened for write");

	write_line(t.types, file);
	write_line(t.hat, file);
	write_line(t.links, file);

	vector<write_f> writers_hat = createWriters(t.types);

	if (t.content.size() != 0)
		write_element_line(t.content[0], writers_hat, file);

	for (size_t i = 1; i < t.content.size(); ++i) {
		file << '\n';
		write_element_line(t.content[i], writers_hat, file);
	}

	//file << "1234";

	file.clear();
	file.seekp(0, ios::beg); 
}


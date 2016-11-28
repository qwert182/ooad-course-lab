#include "DataBase.h"
#include "../IQuery.h"
#include "../DataBaseException.h"

#include <string>
#include <utility>


using std::string;
using std::fstream;
using std::make_pair;
using std::ios;




#ifdef COMPILE_WITH_TESTS
static bool copy_file(const char src[], const char dst[]) {
	std::ifstream i(src, std::ios::binary);
	if (!i.good()) return false;
	i.seekg(0, std::ios::end);
	size_t s = static_cast<size_t>(i.tellg());
	i.seekg(0, std::ios::beg);
	char * buf = static_cast<char *>(malloc(s));
	i.read(buf, s);
	i.close();

	std::ofstream o(dst, std::ios::binary);
	if (!o.good()) return false;
	o.write(buf, s);
	free(buf);

	return true;
}

void DataBase::__add_table_test() {
	if (!copy_file("data/test.bak", "data/test.txt"))
		throw DataBaseException("can't __add_table_test()");
	insert_to_files("test");
}
#endif



void DataBase::clearTableFile(const string &name_of_table) {
	fstream & file = getTableFile(name_of_table);
	string full_filename = "data/" + name_of_table + ".txt";
	file.close();
	file.clear();
	file.open(full_filename, ios::trunc | ios::in | ios::out);
	if (!file.good())
		throw DataBaseException("can't clear file \"" + full_filename + '"');
}


void DataBase::insert_to_files(const string &filename) {
  string full_filename = "data/" + filename + ".txt";
  fstream *file = new fstream(full_filename);

	if (!file->good())
		throw DataBaseException("\n"
			"\t" "can't open file \"" + full_filename + "\"" "\n"
			"\n"
			"\t" "possible cause: bad working directory" "\n"
			"\t" "try: set working directory in project debug properties" "\n"
		);

	this->files.insert(make_pair(filename, file));
}


void DataBase::insert_files() {
  static const char * const f[] = {
	"attachments", "messages",
	"notes", "project_workers",
	"projects", "tasks",
	"users", "usertypes"
  };

	for (int i = 0; i < sizeof f/sizeof*f; ++i)
		insert_to_files(f[i]);
}


void DataBase::delete_files() {
#ifdef COMPILE_WITH_TESTS
	if (files.find("test") != files.end()) {
		files.at("test")->close();
		if (!copy_file("data/test.bak", "data/test.txt"))
			throw DataBaseException("can't __add_table_test()");
	}
#endif

	for (auto iter = files.begin(); iter != files.end(); ++iter)
		delete iter->second;
	files.clear();
}






DataBase::DataBase() : opened(false) {}

DataBase::~DataBase() {
	if (opened) close();
}


void DataBase::open() {
	if (opened)
		throw DataBaseException("already opened");
	opened = true;
	insert_files();
}


void DataBase::close() {
	if (!opened)
		throw DataBaseException("is not opened");
	opened = false;
	delete_files();
}


fstream & DataBase::getTableFile(const string &name_of_table) {
	return *files.at(name_of_table);
}



const ITable * DataBase::perform(const IQuery &query) {
	if (!query.filled())
		throw DataBaseException("query is not filled");

	return query.perform(*this);
}


#include "DataBase.h"
#include "../IQuery.h"
#include "../DataBaseException.h"

#include <string>
#include <utility>


using std::string;
using std::fstream;
using std::make_pair;




#ifdef COMPILE_WITH_TESTS
void DataBase::__add_test() {
	insert_to_files("test");
}
#endif



void DataBase::insert_to_files(const string &filename) {
  string full_filename = "data/" + filename + ".txt";
  fstream *file = new fstream(full_filename);

	if (!file->good())
		throw DataBaseException("can't open file \"" + full_filename + '"');

	this->files.insert(make_pair(filename, file));
}


void DataBase::insert_files() {
  static const char * f[] = {
	"attachments", "messages",
	"notes", "project_workers",
	"projects", "tasks",
	"users", "usertypes"
  };

	for (int i = 0; i < sizeof f/sizeof*f; ++i)
		insert_to_files(f[i]);
}


void DataBase::delete_files() {
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


const ITable & DataBase::perform(const IQuery &query) {
	if (!query.filled())
		throw DataBaseException("query is not filled");

	return query.perform(*this);
}




#include "DataBase.h"
#include "../IQuery.h"
#include "../DataBaseException.h"
#include "common.h"

#include <string>
#include <utility>


using std::string;
using std::fstream;
using std::make_pair;
using std::ios;


static const char * const db_files[] = {
	"attachments", "messages",
	"notes", "project_workers",
	"projects", "tasks",
	"users", "usertypes"
};




#ifdef COMPILE_WITH_TESTS

	static void __copy_backup() {
		for (int i = 0; i < sizeof db_files/sizeof*db_files; ++i) {
			string from = "data_backup/" + string(db_files[i]) + ".txt";
			string to = "data_test/" + string(db_files[i]) + ".txt";
			if (!__copy_file(from.c_str(), to.c_str()))
				throw DataBaseException("can't copy \"" + from + "\" to \"" + to + '"');
		}
	}

	static void __delete_backup() {
		for (int i = 0; i < sizeof db_files/sizeof*db_files; ++i) {
			string to = "data_test/" + string(db_files[i]) + ".txt";
			if (_unlink(to.c_str()))
				throw DataBaseException("can't delete \"" + to + '"');
		}
	}


	void DataBase::__insert_test() {
		__copy_backup_test();
		insert_to_files("test");
	}
#endif




string DataBase::getDataDir() const {
#ifdef COMPILE_WITH_TESTS
	if (testOnly || testFull)
		return "data_test/";
	else
#endif
		return "data/";
}


void DataBase::clearTableFile(const string &name_of_table) {
	fstream & file = getTableFile(name_of_table);
	string full_filename = getDataDir() + name_of_table + ".txt";
	file.close();
	file.clear();
	file.open(full_filename, ios::trunc | ios::in | ios::out);
	if (!file.good())
		throw DataBaseException("can't clear file \"" + full_filename + '"');
}


void DataBase::insert_to_files(const string &filename) {
  string full_filename = getDataDir() + filename + ".txt";
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
	for (int i = 0; i < sizeof db_files/sizeof*db_files; ++i)
		insert_to_files(db_files[i]);
}


void DataBase::delete_files() {
	for (auto iter = files.begin(); iter != files.end(); ++iter)
		delete iter->second;
	files.clear();
#ifdef COMPILE_WITH_TESTS
	if (testFull)
		__delete_backup();
	if (testOnly)
		__delete_backup_test();
#endif
}






DataBase::DataBase() : opened(false)
#ifdef COMPILE_WITH_TESTS
	, testOnly(false), testFull(false)
#endif
{}

#ifdef COMPILE_WITH_TESTS
	DataBase::DataBase(_TestOnly *) : opened(false), testOnly(true), testFull(false) {}
	DataBase::DataBase(_TestFull *) : opened(false), testOnly(false), testFull(true) {}
#endif



DataBase::~DataBase() {
	if (opened) close();
}


void DataBase::open() {
	if (opened)
		throw DataBaseException("already opened");

#ifdef COMPILE_WITH_TESTS
	if (testFull)
		__copy_backup();

	if (testOnly)
		__insert_test();
	else
#endif
		insert_files();

	opened = true;
}


void DataBase::close() {
	if (!opened)
		throw DataBaseException("is not opened");
	opened = false;
	delete_files();
}


fstream & DataBase::getTableFile(const string &name_of_table) {
	auto found = files.find(name_of_table);
	if (found == files.end())
		throw DataBaseException("table \"" + name_of_table + "\" not found");
	return *found->second;
}



const ITable * DataBase::perform(const IQuery &query) {
	if (!opened)
		throw DataBaseException("is not opened");

	if (!query.filled())
		throw DataBaseException("query is not filled");

	return query.perform(*this);
}





#include "../instance.h"


IDataBase *dataBase;


void DataBase::CreateTestInstance() {
	dataBase = new DataBase(TESTFULL);
}


void DataBase::CreateInstance() {
	dataBase = new DataBase();
}


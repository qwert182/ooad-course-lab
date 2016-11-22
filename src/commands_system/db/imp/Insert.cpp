#include "../Insert.h"

using namespace std;

ITable & Insert::perform(DataBase &db) const {
	return *(ITable*)nullptr;
}

	bool Insert::filled() const {
		return filled_into && filled_values;
	}

Insert::Insert() {

}

Insert & Insert::into(const string &table, const vector<string> &columns) {
	this->table = table;
	this->columns = columns;
	filled_into = true;
	return *this;
}

Insert & Insert::values(const vector<Element> &columnValues) {
	this->columnValues = columnValues;
	filled_values = true;
	return *this;
	}

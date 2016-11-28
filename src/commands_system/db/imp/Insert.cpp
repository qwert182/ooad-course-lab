#include "../Insert.h"
#include "DataBase.h"
#include "parser.h"
#include "writer.h"
#include "../DataBaseException.h"

using namespace std;

ITable * Insert::perform(DataBase &db) const {
	fstream &file = db.getTableFile(this->table);
	TableWithHeader t = parse(file);

	t.content.push_back(this->columnValues);

	db.clearTableFile(this->table);
	write(t, file);

	return nullptr;
}

bool Insert::filled() const {
	return filled_into && filled_values;
}

Insert::Insert() {

}

Insert & Insert::into(const string &table, const vector<string> &columnNames) {
	this->table = table;
	this->columnNames = columnNames;
	filled_into = true;
	return *this;
}

Insert & Insert::values(const vector<Element> &columnValues) {
	this->columnValues = columnValues;
	filled_values = true;
	return *this;
}


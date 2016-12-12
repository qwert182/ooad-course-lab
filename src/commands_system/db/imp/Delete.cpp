#include "../Delete.h"
#include "../ITable.h"

#include "DataBase.h"
#include "parser.h"
#include "writer.h"
#include "common.h"

using std::vector;
using std::string;
using std::fstream;


ITable * Delete::perform(DataBase &db) const {
	fstream &file = db.getTableFile(this->table);
	TableWithHeader t = parse(file);

	size_t j = findColumnIndexByColumnName(t.hat, this->whereEqual.first);

	vector<vector<Element>> table_after_delete;
	for (size_t i = 0; i < t.content.size(); ++i) {
		if (!(t.content[i][j] == this->whereEqual.second)) {
			table_after_delete.push_back(t.content[i]);
		}
	}

	t.content = table_after_delete;
	db.clearTableFile(this->table);
	write(t, file);

	return nullptr;
};



bool Delete::filled() const {
	return filled_from && filled_where;
}

Delete::Delete() {
	filled_from = false;
	filled_where = false;
}

Delete & Delete::from(const string &table) {
	this->table = table;
	filled_from = true;
	return *this;
}

Delete & Delete::where(const string &column, const Element &equal) {
	this->whereEqual = make_pair(column, equal);
	filled_where = true;
	return *this;
}


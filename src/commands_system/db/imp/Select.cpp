#include "../Select.h"
#include "Table.h"
#include "parser.h"
#include "DataBase.h"
#include "../DataBaseException.h"


#include "common.h"


using std::vector;
using std::string;





vector <Element> Select::selectColumns(const vector<string> &hat, const vector <Element> &all_columns) const {
	vector <Element> result;

	for (size_t i = 0; i < this->columnNames.size(); ++i) {
		size_t j = findColumnIndexByColumnName(hat, this->columnNames[i]);

		result.push_back(all_columns[j]);
	}
	return result;
}



// выполнить запрос Select

ITable * Select::perform(DataBase &db) const {
	TableWithHeader t = parse(db.getTableFile(this->table));

	vector<vector<Element>> result;
	if (this->filled_where) {
		size_t j = findColumnIndexByColumnName(t.hat, this->whereEqual.first);

		for (size_t i = 0; i < t.content.size(); ++i) {
			if (t.content[i][j] == this->whereEqual.second) {
				result.push_back(selectColumns(t.hat, t.content[i]));
			}
		}
	} else {
		result.reserve(t.content.size());
		for (size_t i = 0; i < t.content.size(); ++i) {
			result.push_back(selectColumns(t.hat, t.content[i]));
		}
	}

	return new Table(result);
};


// для заполнения

bool Select::filled() const {
	return filled_from;
}

Select::Select(const vector<string> &columnNames) {
	this->columnNames = columnNames;
	filled_from = false;
	filled_where = false;
}

Select & Select::from(const string &table) {
	this->table = table;
	filled_from =true;
	return *this;
}

Select & Select::where(const string &columnName, const Element &equal) {
	this->whereEqual = make_pair(columnName, equal);
	filled_where = true;
	return *this;
}


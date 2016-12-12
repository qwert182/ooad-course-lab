#include "../Update.h"
#include "Table.h"
#include "DataBase.h"
#include "common.h"
#include "parser.h"
#include "writer.h"


using namespace std;


ITable * Update::perform(DataBase &db) const {
	fstream &file = db.getTableFile(this->table);
	TableWithHeader t = parse(file);

	size_t id = findColumnIndexByColumnName(t.hat, this->whereEqual.first);

	for (size_t i = 0; i < t.content.size(); ++i) {
		if (t.content[i][id] == this->whereEqual.second) {
			for (size_t k = 0; k < this->setEqual.size(); ++k) {
				size_t j = findColumnIndexByColumnName(t.hat, this->setEqual[k].first);
				t.content[i][j] = this->setEqual[k].second;
			}
		}
	}

	db.clearTableFile(this->table);
	write(t, file);

	return nullptr;
}




Update::Update(const string &table) : filled_set(false), filled_where(false) {
	this->table = table;
}

Update & Update::set(const vector<pair<string, Element> > &set) {
	this->setEqual = set;
	filled_set = true;
	return *this;
}

Update & Update::where(const string &columnName, const Element &equal) {
	this->whereEqual = make_pair(columnName, equal);
	filled_where = true;
	return *this;
}



bool Update::filled() const {
	return filled_set && filled_where;
}

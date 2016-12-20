#include "../Insert.h"
#include "DataBase.h"
#include "parser.h"
#include "writer.h"
#include "Table.h"
#include "../DataBaseException.h"
#include <algorithm>

using namespace std;

static bool is_needed_key(const vector<string> &columnNames, const TableWithHeader &t) {
	auto found_key = find(t.links.begin(), t.links.end(), "key");
	if (found_key == t.links.end())
		return false;

	const string &key_column_name = t.hat[found_key - t.links.begin()];
	auto found_column_key = find(columnNames.begin(), columnNames.end(), key_column_name);
	if (found_column_key == columnNames.end())
		return true;
	else
		throw DataBaseException("You are not allowed to insert key (id)");
}


int create_id(TableWithHeader &t, int idIndex) {
	int num = t.content.size();
	int max = t.content[0][idIndex];
	int cur;

	for(int j = 1; j < num; j++) {
		cur = t.content[j][idIndex];

		if(max < cur) {
			max = cur;
		}
	}

	max++;
	return max;
}


ITable * Insert::perform(DataBase &db) const {
	size_t i;
	int new_id = -1;
	fstream &file = db.getTableFile(this->table);
	TableWithHeader t = parse(file);
	is_needed_key(this->columnNames, t);
	
	vector<Element> corrected_line;
	
	for (i = 0; i < t.hat.size(); ++i) {
		if (t.links[i] == "key") {
			new_id = create_id(t, i);						
			corrected_line.push_back(new_id);
		} else {
			auto found = find(this->columnNames.begin(), this->columnNames.end(), t.hat[i]);
			if (found == this->columnNames.end())
				throw DataBaseException("Column \"" + t.hat[i] + "\" not found");
			size_t found_index = found - this->columnNames.begin();
			Element element = this->columnValues[found_index];
			corrected_line.push_back(element);
		}
	}

	t.content.push_back(corrected_line);

	//t.content.push_back(this->columnValues);

	db.clearTableFile(this->table);
	write(t, file);

	return new Table(vector<vector<Element> > (1, corrected_line));
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


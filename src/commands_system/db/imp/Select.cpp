#include "../Select.h"
#include "Table.h"
#include "parser.h"
#include "DataBase.h"
#include "../DataBaseException.h"


#include <algorithm>

using namespace std;


// выполнить запрос Select

ITable & Select::perform(DataBase &db) const {
  TableWithHeader t = parse(db.getTableFile(this->table));

  auto found = find(t.hat.begin(), t.hat.end(), whereEqual.first);
  size_t j;
	if (found == t.hat.end())
		throw DataBaseException("table doesn't contain column \"" + whereEqual.first + '"');

	j = found - t.hat.begin();


  vector<vector<Element>> selected_content;

	for (size_t i = 0; i < t.content.size(); ++i)
		if (t.content[i][j] == whereEqual.second)
			selected_content.push_back(t.content[i]);

	return *new Table(selected_content);
};






// для заполнения

bool Select::filled() const {
	return filled_from && filled_where;
}

Select::Select(const vector<string> &columns) {
	this->columns = columns;
	filled_from = false;
	filled_where = false;
}

Select & Select::from(const string &table) {
	this->table = table;
	filled_from =true;
	return *this;
}

Select & Select::where(const string &column, const Element &equal) {
	this->whereEqual = make_pair(column, equal);
	filled_where = true;
	return *this;
}
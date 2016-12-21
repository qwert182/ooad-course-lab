#include "Table.h"
#include <sstream>
#include <string>
#include "../DataBaseException.h"

using std::vector;

int Table::getRowCount() const {
	return content.size();
}


int Table::getColCount() const {
	if (content.size() == 0)
		return 0;
	return content[0].size();
}


const Element & Table::get(int row, int col) const {
	if (!(0<=row && (size_t)row<content.size()))
		throw DataBaseException("row index is out of bounds");
	if (!(0<=col && (size_t)col<content[0].size()))
		throw DataBaseException("column index is out of bounds");
	return content[row][col];
}

Table::Table(const vector<vector<Element>> &parsed_table) {
	content = parsed_table;
}


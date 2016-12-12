#include "Table.h"
#include <sstream>
#include <string>


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
	//if (!(0<=row && row<=content.size()))
	//	throw
	return content[row][col];
}

Table::Table(const vector<vector<Element>> &parsed_table) {
	content = parsed_table;
}


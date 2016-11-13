#include "Table.h"


int Table::getRowCount() const {

	return content.size();
}


 int Table::getColCount() const {
	 return content[0].size();
 }


const  Element & Table::get(int row, int col) const {
	//if (!(0<=row && row<=content.size()))
	//	throw 
	return content[row][col];
}

Table::Table(const std::vector<std::vector<Element>> &content) {
	this->content=content;
}
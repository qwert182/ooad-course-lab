#include "Table.h"
#include "../../utils/InvalidParameterException.h"
#include <sstream>
#include <string>
using namespace std;

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

Table::Table(const vector<vector<string>> &parsed_table) {
	//Input: {{int, string}, 
	//		  {id, name},
	//		  {key, -},
	//		  {1, Соловьев\x20Дмитрий}}	
	//Output: {{1, Соловьев\x20Дмитрий}}	//остальное-системная инфа ненужная
	if(parsed_table.size() < 3)
		throw InvalidParameterException("Table must contain header");
	content.resize(parsed_table.size()-3);
	for(size_t i=3; i<parsed_table.size(); i++){
		content[i-3].reserve(parsed_table[0].size());
			for(size_t j=0; j<parsed_table[0].size(); j++)
	{
		if (parsed_table[0][j]=="int"){
			istringstream sin=istringstream(parsed_table[i][j]);
			int x;
			sin>>x;
			content[i-3].push_back(x);
		}
		else content[i-3].push_back(parsed_table[i][j]);
	}
}
}
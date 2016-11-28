#pragma once

#include "IQuery.h"
#include "Element.h"
#include <string>
#include <vector>
#include <utility>


class Select : public IQuery {
public:
	virtual class ITable * perform(class DataBase &db) const;
	virtual bool filled() const;

private:
	std::vector<std::string> columnNames;
	std::string table;
	std::pair<std::string, Element> whereEqual;
	bool filled_from;
	bool filled_where;
	std::vector <Element> selectColumns(const std::vector<std::string> &hat, const std::vector <Element> &all_columns) const;

public:
	Select(const std::vector<std::string> &columnNames);
	Select & from(const std::string &table);
	Select & where(const std::string &columnName, const Element &equal);
};


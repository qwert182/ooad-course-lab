#pragma once

#include "IQuery.h"
#include "Element.h"
#include <string>
#include <vector>



class Insert : public IQuery {
public:
	virtual class ITable * perform(class DataBase &db) const;
	virtual bool filled() const;

private:
	std::string table;
	std::vector<std::string> columnNames;
	std::vector<Element> columnValues;
	bool filled_into;
	bool filled_values;

public:
	Insert();
	Insert & into(const std::string &table, const std::vector<std::string> &columnNames);
	Insert & values(const std::vector<Element> &columnValues);
};


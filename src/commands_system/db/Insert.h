#pragma once

#include "IQuery.h"
#include "Element.h"
#include <string>
#include <vector>



class Insert : public IQuery {
public:
	virtual class ITable & perform(class DataBase &db) const;
	virtual bool filled() const;

private:
	std::string table;
	std::vector<std::string> columns;
	std::vector<Element> columnValues;
	bool filled_into;
	bool filled_values;

public:
	Insert();
	Insert & into(const std::string &table, const std::vector<std::string> &columns);
	Insert & values(const std::vector<Element> &columnValues);
};


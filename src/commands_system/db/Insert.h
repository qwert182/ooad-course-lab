#pragma once

#include "IQuery.h"

#include <string>
#include <vector>


class Insert : public IQuery {
public:
	virtual class ITable & perform(const class DataBase &db);

private:
	std::string table;
	std::vector<std::string> columns;
	std::vector<class Element *> columnValues;
public:
	Insert();
	Insert & into(const std::string &table, const std::vector<std::string> &columns);
	Insert & values(const std::vector<class Element *> &columnValues);
};


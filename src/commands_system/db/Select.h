#pragma once

#include "IQuery.h"
#include "Element.h"
#include <string>
#include <vector>
#include <utility>


class Select : public IQuery {
public:
	virtual class ITable & perform(class DataBase &db) const;
	virtual bool filled() const;

private:
	std::vector<std::string> columns;
	std::string table;
	std::pair<std::string, Element> whereEqual;
	bool filled_from;
	bool filled_where;

public:
	Select(const std::vector<std::string> &columns);
	Select & from(const std::string &table);
	Select & where(const std::string &column, const Element &equal);
};


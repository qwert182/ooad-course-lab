#pragma once

#include "IQuery.h"
#include "Element.h"
#include <string>
#include <vector>
#include <utility>


class Update : public IQuery {
public:
	virtual class ITable * perform(class DataBase &db) const;
	virtual bool filled() const;

private:
	std::string table;
	std::vector<std::pair<std::string, Element> > setEqual;
	std::pair<std::string, Element> whereEqual;
	bool filled_set;
	bool filled_where;

public:
	Update(const std::string &table);
	Update & set(const std::vector<std::pair<std::string, Element> > &set);
	Update & where(const std::string &columnName, const Element &equal);
};


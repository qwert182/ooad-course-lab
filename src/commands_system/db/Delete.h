#pragma once

#include "IQuery.h"
#include "Element.h"
#include <string>
#include <utility>



class Delete : public IQuery {
public:
	virtual class ITable * perform(class DataBase &db) const;
	virtual bool filled() const;

private:
	std::string table;
	std::pair<std::string, Element> whereEqual;
	bool filled_from;
	bool filled_where;


public:
	Delete();
	Delete & from(const std::string &table);
	Delete & where(const std::string &column, const Element &equal);
};


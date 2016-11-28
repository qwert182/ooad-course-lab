#pragma once

class IQuery {
public:
	virtual class ITable * perform(class DataBase &db) const = 0;
	virtual bool filled() const = 0;
};


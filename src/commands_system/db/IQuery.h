#pragma once

class IQuery {
public:
	virtual class ITable & perform(const class DataBase &db) = 0;
};


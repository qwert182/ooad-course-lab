#pragma once

class IDataBase {
public:
	virtual void open() = 0;
	virtual void close() = 0;
	virtual class ITable & perform(const class IQuery &query) = 0;
};


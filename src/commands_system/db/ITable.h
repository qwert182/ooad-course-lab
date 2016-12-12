#pragma once

class ITable {
public:
	virtual int getRowCount() const = 0;
	virtual int getColCount() const = 0;
	virtual const class Element & get(int row, int col) const = 0;
	virtual ~ITable() {}
};


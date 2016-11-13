#include "../ITable.h"
#include "../Element.h"
#include <vector>


class Table {
private:
	std::vector<std::vector<Element>> content; //содержимое таблицы
public:
	virtual int getRowCount() const;
	virtual int getColCount() const;
	virtual const class Element & get(int row, int col) const;

	Table(const std::vector<std::vector<Element>> &content);
	// think about ~
};
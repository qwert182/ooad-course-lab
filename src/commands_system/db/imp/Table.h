#include "../ITable.h"
#include "../Element.h"
#include <vector>


class Table : public ITable {
private:
	std::vector<std::vector<Element>> content; //содержимое таблицы
public:
	virtual int getRowCount() const;
	virtual int getColCount() const;
	virtual const Element & get(int row, int col) const;

	Table(const std::vector<std::vector<Element>> &parsed_table);
	virtual ~Table() {}
};
#include "../../utils/Test.h"
#include "../../utils/Assertions.h"
#include "Table.h"

#include <vector>

using std::vector;

TEST(CanCreateTableWithEmptyContent) {
	void test(){
	  vector<vector<Element>> c;
	  Table t(c);
		assertEquals(0, t.getRowCount());
		assertEquals(0, t.getColCount());
	}
} TEST_END;


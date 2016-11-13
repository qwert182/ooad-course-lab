#include "../../utils/Test.h"
#include "../../utils/Assertions.h"
#include "../../utils/InvalidParameterException.h"
#include "Table.h"
using namespace std;

TEST_exception(CannotCreateTableWithEmptyContent, InvalidParameterException){
	void test(){
		vector<vector<string>> c;
		Table t= Table(c); //t=table, c=content

	}
} TEST_END;

TEST(CanCreatePartOfTable2x4){
	void test(){
		vector<vector<string>> c;
		static const char* const a[4][2] = {{"int", "string"}, 
			  {"id", "name"},
			  {"key", "-"},
		  {"1", "—оловьев ƒмитрий"}};	

		c.push_back(vector<string>(&a[0][0], &a[0][2]));
		c.push_back(vector<string>(&a[1][0], &a[1][2]));
		c.push_back(vector<string>(&a[2][0], &a[2][2]));
		c.push_back(vector<string>(&a[3][0], &a[3][2]));

		Table t= Table(c); 
		assertEquals(1, t.getRowCount());
		assertEquals(2, t.getColCount());
		assertEquals((string)"—оловьев ƒмитрий", (string)t.get(0, 1));
		assertEquals(1, (int)t.get(0, 0));
	}
} TEST_END;
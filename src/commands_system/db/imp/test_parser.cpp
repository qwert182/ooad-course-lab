#include "parser.h"
#include "../Element.h"

#include "../../utils/Test.h"
#include "../../utils/Assertions.h"
#include <vector>

using std::vector;
using std::string;

/*
TEST(CanParse){
	void test(){

	}
} TEST_END;
*/

TEST(CanParse){
	void test(){
		parse("users");
	}
} TEST_END;


TEST(CanParseUsers){
	void test(){
		vector <vector <string> > a;
		a = parse("users");
		assertTrue(a.size()!=0);
	}
} TEST_END;


TEST_exception(CannotParseNotExistingFile, ParseFailedException) {
	void test(){
		vector <vector <string> > a;
		a = parse("NotExistingFile");
	}
} TEST_END;


TEST(CanParserReadTableWith5Rows7Columns){
	void test(){
		vector <vector <string> > a;
		a = parse("users");
		// a -вся таблица
		// a vvE
		// a.size - число строк 
		// a[0] vE -первая строчка таблицы
		// a[0].size - длина первой строчки таблицы (число стобцов) (должна совпадать со всеми остальными)
		// a[0][0] - первый элемент первой строки (string или число)

		assertTrue(a.size() == 7); // число строк = 7

		for(size_t i=0; i<a.size(); i++)
			assertTrue(a[i].size() == 5); // число стобцов = 5

		assertEqual((string) "int", (string) a[0][0]);
		assertEqual((string) "3", (string) a[5][0]);
		assertEqual((string) "-", (string) a[2][2]);
		assertEqual((string) "usertypes.txt", (string) a[2][4]);
	}
} TEST_END;

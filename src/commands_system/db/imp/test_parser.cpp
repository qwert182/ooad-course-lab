#include "parser.h"
#include "ParseFailedException.h"
#include "../Element.h"

#include "../../utils/Test.h"
#include "../../utils/Assertions.h"


#include <vector>
#include <string>
#include <fstream>

using std::vector;
using std::string;
using std::ifstream;


TEST(CanParse) {
	void test() {
		ifstream f("data/test.txt");
		parse(f);
	}
} TEST_END;


TEST(CanParseUsers) {
	void test() {
		ifstream f("data/test.txt");
		TableWithHeader t = parse(f);
		assertTrue(t.content.size()!=0);
	}
} TEST_END;


TEST_exception(CannotParseNotExistingFile, ParseFailedException) {
	void test() {
		ifstream f("NotExistingFile");
		parse(f);
	}
} TEST_END;


TEST(CanParserReadTable__data_test_txt__With4Rows5Columns) {
	void test(){
	  ifstream f("data/test.txt");
	  TableWithHeader t = parse(f);
	  vector<vector<Element>> &a = t.content;
	  vector<string> &hat = t.hat;
		// a - вс€ таблица
		// a vvE
		// a.size - число строк
		// a[0] vE - перва€ строчка таблицы
		// a[0].size - длина первой строчки таблицы (число стобцов) (должна совпадать со всеми остальными)
		// a[0][0] - первый элемент первой строки (string или число)

		assertTrue(a.size() == 4); // число строк = 4

		for (size_t i = 0; i < a.size(); ++i)
			assertTrue(a[i].size() == 5); // число стобцов = 5

		assertEquals(3, (int) a[2][0]);
		assertEquals(string("—оловьев ƒмитрий"), (string) a[0][1]);
		assertEquals(string("123"), (string) a[1][3]);
		assertEquals(3, (int) a[3][4]);


		assertEquals(string("id"), hat[0]);
		assertEquals(string("name"), hat[1]);
		assertEquals(string("login"), hat[2]);
		assertEquals(string("password"), hat[3]);
		assertEquals(string("type_id"), hat[4]);
	}
} TEST_END;


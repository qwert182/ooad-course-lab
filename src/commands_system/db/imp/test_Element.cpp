#include "../Element.h"


#include "../../utils/Test.h"
#include "../../utils/Assertions.h"


#include <vector>
#include <array>

using std::string;
using std::vector;





// creation

TEST(CanCreateIntThenGetInt) {
	void test() {
	  Element el = 0;
	  int i = el;
		assertEquals(0, i);
	}
} TEST_END;

TEST_exception(CannotCreateIntThenGetString, WrongTypeException) {
	void test() {
	  Element el = 0;
	  string s = el;
		(void)s;
	}
} TEST_END;

TEST(canCreateStringThenGetString) {
	void test() {
	  Element el = "string";
	  string s = el;
		assertEquals(string("string"), s);
	}
} TEST_END;

TEST_exception(CannotCreateStringThenGetInt, WrongTypeException) {
	void test() {
	  Element el = "string";
	  int i = el;
		(void)i;
	}
} TEST_END;






// vector<Element>

TEST(CanPushbackInVectorDifferentTypeElements) {
	void test() {
		vector<Element> v;
		v.push_back(1);
		v.push_back("2 string");
		v.push_back(3);

		assertEquals(1, int(v[0]));
		assertEquals(string("2 string"), string(v[1]));
		assertEquals(3, int(v[2]));
	}
} TEST_END;






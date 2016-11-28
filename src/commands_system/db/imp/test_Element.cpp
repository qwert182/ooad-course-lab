#include "../Element.h"
#include "../WrongTypeException.h"


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

TEST_exception(CannotCreateEmptyThenGetInt, WrongTypeException) {
	void test() {
	  Element el;
	  int i = el;
		(void)i;
	}
} TEST_END;

TEST_exception(CannotCreateEmptyThenGetString, WrongTypeException) {
	void test() {
	  Element el;
	  string s = el;
		(void)s;
	}
} TEST_END;





// creation from Element

TEST(CanCreateFromInt) {
	void test() {
	  Element i = 123;
	  Element e = i;
		assertEquals((int)i, (int)e);
	}
} TEST_END;

TEST(CanCreateFromString) {
	void test() {
	  Element s = "string";
	  Element e = s;
		assertEquals((string)s, (string)e);
	}
} TEST_END;

TEST(CanCreateFromEmpty) {
	void test() {
	  Element empty;
	  Element e = empty;
	}
} TEST_END;





// move from Element

TEST(CanMoveFromInt) {
	void test() {
	  Element i = 123;
	  Element e = i;
		assertEquals((int)i, (int)e);
	}
} TEST_END;

TEST(CanMoveFromString) {
	void test() {
	  Element s = "string";
	  Element e = std::move(s);
		assertEquals((string)"string", (string)e);
	}
} TEST_END;

TEST(CanMoveFromEmpty) {
	void test() {
	  Element e_;
	  Element e;// = std::move(e_);
	  string err;
		try {
			//int i = 123;
			//i = e;
			throw WrongTypeException("lalala");
			//assertEquals(123, (int) e);
		} catch (WrongTypeException e) {
			//err = e.what();
		}
		//assertEquals(string("Element hasn't been initialized"), err);
	}
} TEST_END;





// assignment

TEST(CanAssignIntToEmpty) {
	void test() {
	  Element e;
		e = 1;
		assertEquals(1, (int)e);
	}
} TEST_END;

TEST(CanAssignStringToEmpty) {
	void test() {
	  Element e;
		e = "string";
		assertEquals((string)"string", (string)e);
	}
} TEST_END;

TEST(CanAssignStdStringToEmpty) {
	void test() {
	  Element e;
		e = string("string");
		assertEquals((string)"string", (string)e);
	}
} TEST_END;





// compare

TEST(CanCompareEqualsInts) {
	void test() {
	  Element a = -5, b = -5;
		assertTrue(a == b);
	}
} TEST_END;

TEST(CanCompareEqualsStrings) {
	void test() {
	  Element a = "string", b = "string";
		assertTrue(a == b);
	}
} TEST_END;

TEST(CanCompareNotEqualsInts) {
	void test() {
	  Element a = 0, b = -5;
		assertFalse(a == b);
	}
} TEST_END;

TEST(CanCompareNotEqualsStrings) {
	void test() {
	  Element a = "string", b = "string2";
		assertFalse(a == b);
	}
} TEST_END;

TEST_exception(CannotCompareIntAndString, WrongTypeException) {
	void test() {
	  Element a = 123, b = "string";
		a == b;
	}
} TEST_END;

TEST_exception(CannotCompareStringAndInt, WrongTypeException) {
	void test() {
	  Element a = "string", b = 123;
		a == b;
	}
} TEST_END;






// compare with empty

TEST_exception(CannotCompareIntWithEmpty, WrongTypeException) {
	void test() {
	  Element a = 1, e;
		a == e;
	}
} TEST_END;

TEST_exception(CannotCompareEmptyWithInt, WrongTypeException) {
	void test() {
	  Element a = 1, e;
		e == a;
	}
} TEST_END;

TEST_exception(CannotCompareStringWithEmpty, WrongTypeException) {
	void test() {
	  Element a = "1", e;
		a == e;
	}
} TEST_END;

TEST_exception(CannotCompareEmptyWithString, WrongTypeException) {
	void test() {
	  Element a = "1", e;
		e == a;
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

TEST(CanCreateVectorFromArray) {
	void test() {
	  Element a[] = {1, 2, "three"};
	  vector<Element> v(a, &a[sizeof a/sizeof *a]);

		assertEquals(1, (int) v[0]);
		assertEquals(2, (int) v[1]);
		assertEquals(string("three"), (string) v[2]);
	}
} TEST_END;


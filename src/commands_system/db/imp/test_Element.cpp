#ifdef COMPILE_WITH_TESTS

#include "../Element.h"
#include "../WrongTypeException.h"


#include "../../utils/Test.h"
#include "../../utils/Assertions.h"


#include <vector>
#include <array>

using std::string;
using std::vector;






static
void assertElementIsEmpty(const Element &e) {
  const string err_expected = "Element hasn't been initialized";
  string err_int, err_str;
  int i = 123;
  string s = "some string";

	try {
		i = e;
	} catch (WrongTypeException e) {
		err_int = e.what();
	}
	assertEquals(123, i);
	assertEquals(err_expected, err_int);

	try {
		s = e;
	} catch (WrongTypeException e) {
		err_str = e.what();
	}
	assertEquals(string("some string"), s);
	assertEquals(err_expected, err_str);
}






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
		assertElementIsEmpty(e);
	}
} TEST_END;





// move from Element

TEST(CanMoveFromInt) {
	void test() {
	  Element i = 123;
	  Element e = std::move(i);
		assertElementIsEmpty(i);
		assertEquals(123, (int)e);
	}
} TEST_END;

TEST(CanMoveFromString) {
	void test() {
	  Element s = "string";
	  Element e = std::move(s);
		assertElementIsEmpty(s);
		assertEquals("string", (string)e);
	}
} TEST_END;

TEST(CanMoveFromEmpty) {
	void test() {
	  Element first;
	  Element second = std::move(first);
		assertElementIsEmpty(first);
		assertElementIsEmpty(second);
	}
} TEST_END;





// assignment

TEST_abstract(WithAllTypes) {
  vector<Element> *all;
	void before() {
		const Element _all[] = {Element(), "string", string("std::string"), 123};
		all = new vector<Element>(_all, _all + sizeof _all/sizeof*_all);
	}
	void after() {
		delete all;
	}
};




TEST_from(CanAssignElementEmpty, WithAllTypes) {
	void test() {
	  Element empty;
		for (size_t i = 0; i < all->size(); ++i) {
			all->at(i) = empty;
			assertElementIsEmpty(all->at(i));
		}
	}
} TEST_END;

TEST_from(CanAssignElementInt, WithAllTypes) {
	void test() {
	  Element integer = 123;
		for (size_t i = 0; i < all->size(); ++i) {
			all->at(i) = integer;
			assertEquals(123, (int) all->at(i));
		}
	}
} TEST_END;


TEST_from(CanAssignElementString, WithAllTypes) {
	void test() {
	  Element str = "string";
		for (size_t i = 0; i < all->size(); ++i) {
			all->at(i) = str;
			assertEquals(string("string"), (string) all->at(i));
		}
	}
} TEST_END;

TEST_from(CanAssignInt, WithAllTypes) {
	void test() {
		for (size_t i = 0; i < all->size(); ++i) {
			all->at(i) = 123;
			assertEquals(123, (int) all->at(i));
		}
	}
} TEST_END;


TEST_from(CanAssignString, WithAllTypes) {
	void test() {
		for (size_t i = 0; i < all->size(); ++i) {
			all->at(i) = "string";
			assertEquals(string("string"), (string) all->at(i));
		}
	}
} TEST_END;

TEST_from(CanAssignStdString, WithAllTypes) {
	void test() {
	  const string str = "string";
		for (size_t i = 0; i < all->size(); ++i) {
			all->at(i) = str;
			assertEquals(string("string"), (string) all->at(i));
		}
	}
} TEST_END;





// move assignment

TEST_from(CanMovingAssignFromInt, WithAllTypes) {
	void test() {
		for (size_t i = 0; i < all->size(); ++i) {{
			  Element integer = 123;
				all->at(i) = std::move(integer);
				assertElementIsEmpty(integer);
				assertEquals(123, (int) all->at(i));
		}}
	}
} TEST_END;

TEST_from(CanMovingAssignFromString, WithAllTypes) {
	void test() {
		for (size_t i = 0; i < all->size(); ++i) {{
			  Element s = "string";
				all->at(i) = std::move(s);
				assertElementIsEmpty(s);
				assertEquals("string", (string) all->at(i));
		}}
	}
} TEST_END;

TEST_from(CanMovingAssignFromEmpty, WithAllTypes) {
	void test() {
		for (size_t i = 0; i < all->size(); ++i) {{
		  Element empty;
			all->at(i) = std::move(empty);
			assertElementIsEmpty(empty);
			assertElementIsEmpty(all->at(i));
		}}
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

TEST_exception(CannotCompareEmptyWithEmpty, WrongTypeException) {
	void test() {
	  Element e1, e2;
		e1 == e2;
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



#endif


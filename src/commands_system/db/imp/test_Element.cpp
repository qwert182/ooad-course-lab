#include "../Element.h"


#include "../../utils/Test.h"
#include "../../utils/Assertions.h"


#include <vector>
#include <array>

using std::string;
using std::vector;





// creation

TEST(can_create_int_then_get_int) {
	void test() {
	  Element el = 0;
	  int i = el;
		assertEqual(0, i);
	}
} TEST_END;

TEST_exception(cannot_create_int_then_get_string, WrongTypeException) {
	void test() {
	  Element el = 0;
	  string s = el;
		(void)s;
	}
} TEST_END;

TEST(can_create_string_then_get_string) {
	void test() {
	  Element el = "string";
	  string s = el;
		assertEqual(string("string"), s);
	}
} TEST_END;

TEST_exception(cannot_create_string_then_get_int, WrongTypeException) {
	void test() {
	  Element el = "string";
	  int i = el;
		(void)i;
	}
} TEST_END;





// equality

TEST(are_equal_integer_elements_equal) {
	void test() {
	  Element
		e1 = 123,
		e2 = 123;
		assertTrue(e1 == e2);
	}
} TEST_END;

TEST(are_equal_string_elements_equal) {
	void test() {
	  Element
		e1 = "string",
		e2 = "string";
		assertTrue(e1 == e2);
	}
} TEST_END;

TEST(are_equal_string_and_element_equal) {
	void test() {
	  string str = "string";
	  Element s = str;
		assertTrue(s == "string");
		assertTrue("string" == s);
		assertTrue(s == str);
		assertTrue(str == s);
	}
} TEST_END;

TEST(are_equal_int_and_element_equal) {
	void test() {
	  Element s = 0;
		assertTrue(s == 0);
		assertTrue(0 == s);
	}
} TEST_END;





// wrong compare

TEST_abstract_exception(wrong_compare_test, WrongTypeException) {
protected:
	Element *s, *i;
public:
	void before() {
		s = new Element("string");
		i = new Element(123);
	}
	void after() {
		delete s;
		delete i;
	}
};

TEST_from(cannot_compare_int_element_and_string_element) : public wrong_compare_test {
	void test() {
		*i == *s;
	}
} TEST_END;

TEST_from(cannot_compare_string_element_and_int_element) : public wrong_compare_test {
	void test() {
		*s == *i;
	}
} TEST_END;

TEST_from(cannot_compare_int_element_and_string) : public wrong_compare_test {
	void test() {
		*i == "string";
	}
} TEST_END;

TEST_from(cannot_compare_string_and_int_element) : public wrong_compare_test {
	void test() {
		"string" == *i;
	}
} TEST_END;

TEST_from(cannot_compare_int_element_and_stdstring) : public wrong_compare_test {
	void test() {
		*i == string("string");
	}
} TEST_END;

TEST_from(cannot_compare_stdstring_and_int_element) : public wrong_compare_test {
	void test() {
		string("string") == *i;
	}
} TEST_END;

TEST_from(cannot_compare_string_element_and_int) : public wrong_compare_test {
	void test() {
		*s == 123;
	}
} TEST_END;

TEST_from(cannot_compare_int_and_string_element) : public wrong_compare_test {
	void test() {
		123 == *s;
	}
} TEST_END;







// vector<Element>

TEST(can_pushback_in_vector_different_type_elements) {
	void test() {
		vector<Element> v;
		v.push_back(1);
		v.push_back("2 string");
		v.push_back(3);

		assertEqual(1, int(v[0]));
		assertEqual(string("2 string"), string(v[1]));
		assertEqual(3, int(v[2]));
	}
} TEST_END;






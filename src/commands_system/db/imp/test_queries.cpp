#include "../Select.h"
#include "../Insert.h"
#include "../Delete.h"
#include "../../utils/Test.h"
#include "../../utils/Assertions.h"

using namespace std;


TEST(CanCreateSelect) {
	void test() {
	  vector<string> a;
		Select q = Select(a).from("table").where("id", 123);
		assertTrue(q.filled());
	}
}TEST_END;

TEST(CanCreateInsert) {
	void test() {
	  vector<string> a;
	  vector<Element> b;
		Insert q = Insert().into("table", a).values(b);
		assertTrue(q.filled());
	}
}TEST_END;

TEST(CanCreateDelete) {
	void test() {
	  Delete q = Delete().from("table").where("id", 123);
		assertTrue(q.filled());
	}
}TEST_END;


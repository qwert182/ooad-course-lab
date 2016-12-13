#include "HTTPServer.h"

#include "../../utils/Test.h"
#include "../../utils/Assertions.h"

#include "HTTPException.h"



TEST(CanCreate) {
	void test() {
		HTTPServer();
	}
} TEST_END;

TEST(CanCreateAsIPresenter) {
	void test() {
		IPresenter *p = new HTTPServer();
		delete p;
	}
} TEST_END;

TEST_exception(CannotCreateTwice, HTTPException) {
  IPresenter *first;
	void before() {
		first = new HTTPServer();
	}
	void after() {
		delete first;
	}
	void test() {
		new HTTPServer();
	}
} TEST_END;

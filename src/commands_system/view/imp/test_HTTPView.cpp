#include "HTTPView.h"

#include "../../utils/Test.h"
#include "../../utils/Assertions.h"

#include "HTTPException.h"



TEST(CanCreate) {
	void test() {
		HTTPView();
	}
} TEST_END;

TEST(CanCreateAsIView) {
	void test() {
		IView *view = new HTTPView();
		delete view;
	}
} TEST_END;

TEST_exception(CannotCreateTwice, HTTPException) {
  IView *first_view;
	void before() {
		first_view = new HTTPView();
	}
	void after() {
		delete first_view;
	}
	void test() {
		new HTTPView();
	}
} TEST_END;

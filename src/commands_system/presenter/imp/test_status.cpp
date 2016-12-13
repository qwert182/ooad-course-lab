#include "utils/status.h"

#include "../../utils/Test.h"
#include "../../utils/assertions.h"

#include <string>

#include "InternalServerErrorException.h"

using std::string;
using std::vector;


static
void assertStatus(const char *line, int code) {
  string expected = line;
	expected.append("\r\n");
  vector<char> actual = getStatusBy(code);
	assertEquals(expected, string(actual.begin(), actual.end()));
}


TEST_exception(Status_CannotGetBad, InternalServerErrorException) {
	void test() {
		getStatusBy(12345);
	}
} TEST_END;


TEST(Status_OK) {
	void test() {
		assertStatus("HTTP/1.1 200 OK", 200);
	}
} TEST_END;


TEST(Status_MovedTemporarily) {
	void test() {
		assertStatus("HTTP/1.1 302 Moved Temporarily", 302);
	}
} TEST_END;


TEST(Status_BadRequest) {
	void test() {
		assertStatus("HTTP/1.1 400 Bad Request", 400);
	}
} TEST_END;


TEST(Status_NotFound) {
	void test() {
		assertStatus("HTTP/1.1 404 Not Found", 404);
	}
} TEST_END;


TEST(Status_InternalServerError) {
	void test() {
		assertStatus("HTTP/1.1 500 Internal Server Error", 500);
	}
} TEST_END;


TEST(Status_NotImplemented) {
	void test() {
		assertStatus("HTTP/1.1 501 Not Implemented", 501);
	}
} TEST_END;


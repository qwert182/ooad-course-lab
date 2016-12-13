#include "utils/parse_post.h"

#include "../../utils/Test.h"
#include "../../utils/Assertions.h"

using std::string;
using std::unordered_map;


static void assert(const unordered_map<string, string> &post) {
  auto notFound = post.end();
	assertTrue(post.find("login") != notFound);
	assertTrue(post.find("password") != notFound);
	assertEquals("root", post.at("login"));
	assertEquals("123", post.at("password"));
	assertEquals((size_t)2, post.size());
}


TEST(Can_parse_post) {
	void test() {
	  unordered_map<string, string> post = parse_post("login=root\r\npassword=123");
		assert(post);
	}
} TEST_END;


TEST(Can_parse_post_CRLF_at_end) {
	void test() {
	  unordered_map<string, string> post = parse_post("login=root\r\npassword=123\r\n");
		assert(post);
	}
} TEST_END;


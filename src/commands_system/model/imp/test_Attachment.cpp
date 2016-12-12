#ifdef COMPILE_WITH_TESTS
#include "test_WithFullDB.h"

#include "Attachment.h"
#include "User.h"


TEST_from(GetFileNameTest, WithFullDB) {
	void test() {		
		IAttachment *attachment = new Attachment(1);
		std::string result = attachment->getFileName();

		assertEquals("documentation.txt", result);
				
		delete attachment;
	}
} TEST_END;

TEST_from(GetDescriptionTest, WithFullDB) {
	void test() {		
		IAttachment *attachment = new Attachment(1);
		std::string result = attachment->getDescription();

		assertEquals("added docs", result);
				
		delete attachment;
	}
} TEST_END;

TEST_from(GetOwnerTest, WithFullDB) {
	void test() {		
		IAttachment *attachment = new Attachment(1);
		IUser *result = attachment->getOwner();
		
		assertEquals("grosheva", result->getLogin());
				
		delete attachment;
		delete result;
	}
} TEST_END;

#endif


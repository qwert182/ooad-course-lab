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

TEST_from(AttachmentConstructorTest, WithFullDB) {
	void test() {		
		IUser *user = new User(1);

		IAttachment *attachment = new Attachment("doc.txt", "desc doc.txt", *user);		
		
		IUser *curUser = attachment->getOwner();

		assertEquals("doc.txt", attachment->getFileName());
		assertEquals("desc doc.txt", attachment->getDescription());
		assertEquals(user->getName(), curUser->getName());
				
		delete attachment;
		delete user;
		delete curUser;
	}
} TEST_END;

#endif


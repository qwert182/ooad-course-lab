#ifdef COMPILE_WITH_TESTS
#include "test_WithFullDB.h"

#include "User.h"
#include "Message.h"


TEST_from(GetSenderTest, WithFullDB) {
	void test() {
		
		IMessage *message = new Message(1);
		IUser *result = message->getSender();

		assertEquals("volkov", result->getLogin());
				
		delete message;
		delete result;
	}
} TEST_END;

TEST_from(GetReceiverTest, WithFullDB) {
	void test() {
		
		IMessage *message = new Message(1);
		IUser *result = message->getReceiver();

		assertEquals("solovev", result->getLogin());
				
		delete message;
		delete result;
	}
} TEST_END;

TEST_from(GetSubjectTest, WithFullDB) {
	void test() {
		
		IMessage *message = new Message(1);
		std::string result = message->getSubject();

		assertEquals("time", result);
				
		delete message;
	}
} TEST_END;

TEST_from(GetTextTest, WithFullDB) {
	void test() {
		
		IMessage *message = new Message(1);
		std::string result = message->getText();

		assertEquals("you're late", result);
				
		delete message;
	}
} TEST_END;


#endif


#ifdef COMPILE_WITH_TESTS
#include "test_WithFullDB.h"

#include "User.h"
#include "Mail.h"
#include "Message.h"


TEST_from(GetInBoxTest_IsNotEmpty, WithFullDB) {
	void test() {
		User *user = new User(4);
		IMail *mailInBox = new Mail(user);
		std::vector<class IMessage *> result = mailInBox->getOutBox();
		
		IUser *u = result[0]->getSender();

		assertEquals("volkov", u->getLogin());

		int n = result.size();
		for(int i = 0; i < n; i++) {
			delete result[i];
		}		
		
		delete mailInBox;
		delete user;
		delete u;
	}
} TEST_END;

TEST_from(GetInBoxTest_IsEmpty, WithFullDB) {
	void test() {
		User *user = new User(1);
		IMail *mailInBox = new Mail(user);
		std::vector<class IMessage *> result = mailInBox->getOutBox();		
		
		assertEquals(true, result.empty());
		
		delete mailInBox;
		delete user;
	}
} TEST_END;

TEST_from(GetOutBoxTest_IsNotEmpty, WithFullDB) {
	void test() {
		User *user = new User(1);
		IMail *mailOutBox = new Mail(user);
		std::vector<class IMessage *> result = mailOutBox->getInBox();
		
		IUser *u = result[0]->getReceiver();

		assertEquals("solovev", u->getLogin());

		int n = result.size();
		for(int i = 0; i < n; i++) {
			delete result[i];
		}		
		
		delete mailOutBox;
		delete user;
		delete u;
	}
} TEST_END;

TEST_from(GetOutBoxTest_IsEmpty, WithFullDB) {
	void test() {
		User *user = new User(2);
		IMail *mailOutBox = new Mail(user);
		std::vector<class IMessage *> result = mailOutBox->getInBox();

		assertEquals(true, result.empty());
		
		delete mailOutBox;
		delete user;
	}
} TEST_END;

#endif


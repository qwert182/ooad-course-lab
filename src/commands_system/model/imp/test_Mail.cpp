#ifdef COMPILE_WITH_TESTS
#include "test_WithFullDB.h"

#include "User.h"
#include "Mail.h"
#include "Message.h"


TEST_from(GetInBoxTest_IsNotEmpty, WithFullDB) {
	void test() {
		User *user = new User(4);
		IMail *mailInBox = new Mail(user);
		std::vector<class IMessage *> result = mailInBox->getInBox();
		
		assertEquals("volkov", result[0]->getSender()->getLogin());

		int n = result.size();
		for(int i = 0; i < n; i++) {
			delete result[i];
		}		
		
		delete mailInBox;
		delete user;
	}
} TEST_END;




#endif


#ifdef COMPILE_WITH_TESTS
#include "test_WithFullDB.h"


#include "User.h"




TEST_from(CanCreateUserFromDatabase, WithFullDB) {
	void test() {
		IUser *user = new User(4);
		assertEquals("Волков Денис", user->getName());
		assertEquals("volkov", user->getLogin());
		assertEquals("denwolf", user->getPassword());
		delete user;
	}
} END_TEST;




#endif


#ifdef COMPILE_WITH_TESTS
#include "test_WithFullDB.h"

#include "User.h"
#include "UserType.h"

TEST_from(CanCreateUserFromDatabase_1, WithFullDB) {
	void test() {
		IUser *user = new User(4);

		assertEquals("Волков Денис", user->getName());
		assertEquals("volkov", user->getLogin());
		assertEquals("denwolf", user->getPassword());

		delete user;
	}
} TEST_END;

TEST_from(CanCreateUserFromDatabase_2, WithFullDB) {
	void test() {
		IUser *user = new User(2);

		assertEquals("Грошева Людмила", user->getName());
		assertEquals("grosheva", user->getLogin());
		assertEquals("123", user->getPassword());

		delete user;
	}
} TEST_END;

TEST_from(GetUserTypeTest_1, WithFullDB) {
	void test() {
		IUser *user = new User(4);
		IUserType *userType = user->getType();
		
		assertEquals("manager", userType->getName());

		delete userType;
		delete user;
	}
} TEST_END;

TEST_from(GetUserTypeTest_2, WithFullDB) {
	void test() {
		IUser *user = new User(1);
		IUserType *userType = user->getType();
		
		assertEquals("admin", userType->getName());

		delete userType;
		delete user;
	}
} TEST_END;


#endif


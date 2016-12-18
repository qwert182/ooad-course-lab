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

TEST_from(SetUserNameTest, WithFullDB) {
	void test() {
		IUser *user = new User(1);
		user->setName("DD");
		
		assertEquals("DD", user->getName());
		
		delete user;
	}
} TEST_END;

TEST_from(SetUserLoginTest, WithFullDB) {
	void test() {
		IUser *user = new User(1);
		user->setLogin("dd");
		
		assertEquals("dd", user->getLogin());
		
		delete user;
	}
} TEST_END;

TEST_from(SetUserPasswordTest, WithFullDB) {
	void test() {
		IUser *user = new User(1);
		user->setPassword("111");
		
		assertEquals("111", user->getPassword());
		
		delete user;
	}
} TEST_END;

TEST_from(SetUserTypeTest, WithFullDB) {
	void test() {
		IUser *user = new User(1);
		IUserType *type = new UserType(1);
		user->setType(*type);
		IUserType *resType = user->getType();
		
		assertEquals("admin", resType->getName());
		
		delete resType;
		delete type;
		delete user;
	}
} TEST_END;

TEST_from(UserConstructorWithOutTypeTest, WithFullDB) {
	void test() {
		IUser *user = new User("Max", "max", "123");		
				
		assertEquals("Max", user->getName());
		assertEquals("max", user->getLogin());
		assertEquals("123", user->getPassword());

		delete user;
	}
} TEST_END;

TEST_from(UserConstructorWithTypeTest, WithFullDB) {
	void test() {
		IUserType *type = new UserType(2);
		IUser *user = new User("Mike", "mike", "555", *type);		
				
		IUserType *curType = user->getType();
		
		assertEquals("Mike", user->getName());
		assertEquals("mike", user->getLogin());
		assertEquals("555", user->getPassword());
		assertEquals(type->getName(), curType->getName());

		delete curType;
		delete user;
		delete type;
	}
} TEST_END;


#endif


#ifdef COMPILE_WITH_TESTS
#include "test_WithFullDB.h"

#include "User.h"
#include "UserType.h"


TEST_from(GetNameTest_1, WithFullDB) {
	void test() {
		
		IUserType *userType = new UserType(1);
		std::string result = userType->getName();

		assertEquals("admin", result);
				
		delete userType;
	}
} TEST_END;

TEST_from(GetNameTest_2, WithFullDB) {
	void test() {
		
		IUserType *userType = new UserType(2);
		std::string result = userType->getName();

		assertEquals("user", result);
				
		delete userType;
	}
} TEST_END;

TEST_from(IsManagerTest_True, WithFullDB) {
	void test() {
		
		IUserType *userType = new UserType(3);
		bool result = userType->isManager();

		assertEquals(true, result);
				
		delete userType;
	}
} TEST_END;

TEST_from(IsManagerTest_False, WithFullDB) {
	void test() {
		
		IUserType *userType = new UserType(1);
		bool result = userType->isManager();

		assertEquals(false, result);
				
		delete userType;
	}
} TEST_END;

TEST_from(IsAdminTest_True, WithFullDB) {
	void test() {
		
		IUserType *userType = new UserType(1);
		bool result = userType->isAdmin();

		assertEquals(true, result);
				
		delete userType;
	}
} TEST_END;

TEST_from(IsAdminTest_False, WithFullDB) {
	void test() {
		
		IUserType *userType = new UserType(2);
		bool result = userType->isAdmin();

		assertEquals(false, result);
				
		delete userType;
	}
} TEST_END;

TEST_from(SetNameTest, WithFullDB) {
	void test() {
		
		IUserType *userType = new UserType(1);
		userType->setName("manager");
		
		assertEquals("manager", userType->getName());
				
		delete userType;
	}
} TEST_END;

TEST_from(UserTypeConstructorTest, WithFullDB) {
	void test() {		
		IUserType *userType = new UserType("quest", 3);		
			
		assertEquals("quest", userType->getName());
		assertFalse(userType->isAdmin());
		assertFalse(userType->isManager());
				
		delete userType;
	}
} TEST_END;

#endif


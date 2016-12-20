#ifdef COMPILE_WITH_TESTS
#include "test_WithFullDB.h"

#include "User.h"
#include "AllUsers.h"
#include "../RegForm.h"

TEST_from(GetAllUsersTest, WithFullDB) {
	void test() {
		
		IAllUsers *allUsers = new AllUsers();
		std::vector<class IUser *> result = allUsers->getUsers();

		assertEquals("solovev", result[0]->getLogin());
		assertEquals("grosheva", result[1]->getLogin());

		int n = result.size();
		for(int i = 0; i < n; i++) {
			delete result[i];
		}
		
		delete allUsers;
	}
} TEST_END;

TEST_from(SignUpTest, WithFullDB) {
	void test() {		
		IAllUsers *allUsers = new AllUsers();
		
		RegForm regForm;
		regForm.name = "userName";
		regForm.login = "userLogin";
		regForm.password = "userPass";

		IUser* user;
		user = allUsers->signUp(regForm);
				
		assertEquals("userName", user->getName());
		assertEquals("userLogin", user->getLogin());
		assertEquals("userPass", user->getPassword());
		
		delete user;
		delete allUsers;
	}
} TEST_END;


#endif


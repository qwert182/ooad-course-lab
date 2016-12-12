#ifdef COMPILE_WITH_TESTS
#include "test_WithFullDB.h"

#include "User.h"
#include "AllUsers.h"


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




#endif


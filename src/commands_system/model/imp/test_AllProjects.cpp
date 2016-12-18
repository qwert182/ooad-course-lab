#ifdef COMPILE_WITH_TESTS
#include "test_WithFullDB.h"

#include "AllProjects.h"
#include "User.h"
#include "Project.h"


TEST_from(GetProjectsTest_IsNotEmpty_1, WithFullDB) {
	void test() {
		User *user = new User(2);
		IAllProjects *allProjects = user->getProjects();
		std::vector<class IProject *> result = allProjects->getProjects();
		
		assertEquals("OOAD", result[0]->getName());

		int n = result.size();
		for(int i = 0; i < n; i++) {
			delete result[i];
		}		
		
		delete allProjects;
		delete user;
	}
} TEST_END;

TEST_from(GetProjectsTest_IsNotEmpty_2, WithFullDB) {
	void test() {
		User *user = new User(3);
		IAllProjects *allProjects = user->getProjects();
		std::vector<class IProject *> result = allProjects->getProjects();
		
		assertEquals("OOAD", result[0]->getName());

		int n = result.size();
		for(int i = 0; i < n; i++) {
			delete result[i];
		}		
		
		delete allProjects;
		delete user;
	}
} TEST_END;


TEST_from(GetProjectsTest_IsEmpty, WithFullDB) {
	void test() {
		User *user = new User(1);
		IAllProjects *allProjects = user->getProjects();
		std::vector<class IProject *> result = allProjects->getProjects();
		
		assertEquals(true, result.empty());
				
		delete allProjects;
		delete user;
	}
} TEST_END;


#endif


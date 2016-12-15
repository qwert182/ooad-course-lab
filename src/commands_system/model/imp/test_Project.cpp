#ifdef COMPILE_WITH_TESTS
#include "test_WithFullDB.h"

#include "Project.h"
#include "User.h"
#include "Task.h"


TEST_from(GetNameTest, WithFullDB) {
	void test() {
		
		IProject *project = new Project(1);
		std::string result = project->getName();

		assertEquals("OOAD", result);
				
		delete project;
	}
} TEST_END;

TEST_from(GetDescriptionTest, WithFullDB) {
	void test() {		
		IProject *project = new Project(1);
		std::string result = project->getDescription();

		assertEquals("create a program", result);
				
		delete project;
	}
} TEST_END;

TEST_from(GetWorkers_IsNotEmpty, WithFullDB) {
	void test() {		
		IProject *project = new Project(1);
		std::vector<class IUser *> result = project->getWorkers();
		
		assertEquals("grosheva", result[0]->getLogin());
		assertEquals("volkov", result[1]->getLogin());
		assertEquals("ryabinkin", result[2]->getLogin());
				
		int n = result.size();
		for(int i = 0; i < n; i++) {
			delete result[i];
		}

		delete project;
	}
} TEST_END;

TEST_from(GetWorkers_IsEmpty, WithFullDB) {
	void test() {		
		IProject *project = new Project(2);
		std::vector<class IUser *> result = project->getWorkers();
		
		assertEquals(true, result.empty());
		
		delete project;
	}
} TEST_END;

TEST_from(GetTasks_IsNotEmpty, WithFullDB) {
	void test() {		
		IProject *project = new Project(1);
		std::vector<class ITask *> result = project->getTasks();
		
		assertEquals("DB", result[0]->getName());
		assertEquals("methodology", result[1]->getName());
				
		int n = result.size();
		for(int i = 0; i < n; i++) {
			delete result[i];
		}

		delete project;
	}
} TEST_END;

TEST_from(GetTasks_IsEmpty, WithFullDB) {
	void test() {		
		IProject *project = new Project(2);
		std::vector<class ITask *> result = project->getTasks();
		
		assertEquals(true, result.empty());

		delete project;
	}
} TEST_END;

TEST_from(SetNameTest, WithFullDB) {
	void test() {
		
		IProject *project = new Project(1);
		project->setName("Lab");
		
		assertEquals("Lab", project->getName());
				
		delete project;
	}
} TEST_END;

TEST_from(SetDescriptionTest, WithFullDB) {
	void test() {		
		IProject *project = new Project(1);
		project->setDescription("Making Lab");

		assertEquals("Making Lab", project->getDescription());
				
		delete project;
	}
} TEST_END;

TEST_from(ProjectConstructor, WithFullDB) {
	void test() {		
		IProject *project = new Project("Making Lab", "You must make lab");		
		
		assertEquals("Making Lab", project->getName());
		assertEquals("You must make lab", project->getDescription());
				
		delete project;
	}
} TEST_END;

TEST_from(AddWorkerToProject, WithFullDB) {
	void test() {		
		IProject *project = new Project(1);		
		IUser *user = new User(1);

		project->add(*user);

		std::vector<class IUser *> workers = project->getWorkers();
		IUser *curUser;
		int len = workers.size();
		bool haveUser = false;

		for(int i = 0; i < len; i++) {
			curUser = workers[i];

			if(curUser->getLogin() == user->getLogin()) {
				haveUser = true;
			} 

			delete curUser;
		}

		assertTrue(haveUser);
		
		delete user;
		delete project;
	}
} TEST_END;

TEST_from(AddTaskTest, WithFullDB) {
	void test() {		
		IProject *project = new Project(1);
		ITask *task = new Task("Testing", "Test Project", "Testing project add task"); 		

		project->add(*task);

		std::vector<class ITask *> result = project->getTasks();
		ITask *curTask;
		int len = result.size();
		bool haveTask = false;

		for(int i = 0; i < len; i++) {
			curTask = result[i];

			if(task->getName() == curTask->getName()) {
				haveTask = true;
			}
			
			delete curTask;
		}
		
		assertTrue(haveTask);
		
		delete task;
		delete project;
	}
} TEST_END;


#endif


#ifdef COMPILE_WITH_TESTS
#include "test_WithFullDB.h"

#include "Task.h"
#include "Note.h"
#include "User.h"
#include "Attachment.h"


TEST_from(GetNameTest_1, WithFullDB) {
	void test() {		
		ITask *task = new Task(1);
		std::string result = task->getName();
		
		assertEquals("DB", result);
				
		delete task;
	}
} TEST_END;

TEST_from(GetNameTest_2, WithFullDB) {
	void test() {		
		ITask *task = new Task(2);
		std::string result = task->getName();
		
		assertEquals("methodology", result);
				
		delete task;
	}
} TEST_END;

TEST_from(GetThemeTest_1, WithFullDB) {
	void test() {		
		ITask *task = new Task(1);
		std::string result = task->getTheme();
		
		assertEquals("task", result);
				
		delete task;
	}
} TEST_END;

TEST_from(GetThemeTest_2, WithFullDB) {
	void test() {		
		ITask *task = new Task(2);
		std::string result = task->getTheme();
		
		assertEquals("seminar", result);
				
		delete task;
	}
} TEST_END;

TEST_from(GetDescriptionTest_1, WithFullDB) {
	void test() {		
		ITask *task = new Task(1);
		std::string result = task->getDescription();
		
		assertEquals("create database", result);
				
		delete task;
	}
} TEST_END;

TEST_from(GetDescriptionTest_2, WithFullDB) {
	void test() {		
		ITask *task = new Task(2);
		std::string result = task->getDescription();
		
		assertEquals("choose architecture", result);
				
		delete task;
	}
} TEST_END;

TEST_from(GetNotesTest_IsNotEmpty, WithFullDB) {
	void test() {		
		ITask *task = new Task(1);
		std::vector<INote *> result = task->getNotes();
		
		assertEquals("unknown exception", result[0]->getText());
		assertEquals("need more info", result[1]->getText());
		assertEquals("ATTACHMENT", result[2]->getText());
				
		int n = result.size();
		for(int i = 0; i < n; i++) {
			delete result[i];
		}

		delete task;
	}
} TEST_END;

TEST_from(GetNotesTest_IsEmpty, WithFullDB) {
	void test() {		
		ITask *task = new Task(2);
		std::vector<INote *> result = task->getNotes();
		
		assertEquals(true, result.empty());
		
		delete task;
	}
} TEST_END;

TEST_from(GetAttachmentsTest_IsNotEmpty, WithFullDB) {
	void test() {		
		ITask *task = new Task(1);
		std::vector<IAttachment *> result = task->getAttachments();
		
		assertEquals("documentation.txt", result[0]->getFileName());
				
		int n = result.size();
		for(int i = 0; i < n; i++) {
			delete result[i];
		}

		delete task;
	}
} TEST_END;

TEST_from(GetAttachmentsTest_IsEmpty, WithFullDB) {
	void test() {		
		ITask *task = new Task(2);
		std::vector<IAttachment *> result = task->getAttachments();
		
		assertEquals(true, result.empty());
		
		delete task;
	}
} TEST_END;

TEST_from(SetNameTest, WithFullDB) {
	void test() {		
		ITask *task = new Task(1);
		task->setName("Pass Exam");
		
		assertEquals("Pass Exam", task->getName());
				
		delete task;
	}
} TEST_END;

TEST_from(SetThemeTest, WithFullDB) {
	void test() {		
		ITask *task = new Task(1);
		task->setTheme("We Must Pass Exam");
		
		assertEquals("We Must Pass Exam", task->getTheme());
				
		delete task;
	}
} TEST_END;

TEST_from(SetDescriptionTest, WithFullDB) {
	void test() {		
		ITask *task = new Task(1);
		task->setDescription("We Must Pass Exam on the next week");
		
		assertEquals("We Must Pass Exam on the next week", task->getDescription());
				
		delete task;
	}
} TEST_END;

TEST_from(TaskConstructorTest, WithFullDB) {
	void test() {		
		ITask *task = new Task("Testing", "Test Task", "Testing task constructor");
		
		assertEquals("Testing", task->getName());
		assertEquals("Test Task", task->getTheme());
		assertEquals("Testing task constructor", task->getDescription());
				
		delete task;
	}
} TEST_END;

TEST_from(AddNoteTest, WithFullDB) {
	void test() {		
		ITask *task = new Task(1);
		IUser *user = new User(2);
		INote *note = new Note(*user, "Testing note add task"); 		

		task->add(*note);

		std::vector<class INote *> result = task->getNotes();
		INote *curNote;
		int len = result.size();
		bool haveNote = false;

		for(int i = 0; i < len; i++) {
			curNote = result[i];

			if(note->getText() == curNote->getText()) {
				haveNote = true;
			}
			
			delete curNote;
		}
		
		assertTrue(haveNote);
		
		delete task;
		delete user;
		delete note;
	}
} TEST_END;


#endif


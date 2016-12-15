#ifdef COMPILE_WITH_TESTS
#include "test_WithFullDB.h"

#include "Attachment.h"
#include "User.h"
#include "Note.h"


TEST_from(GetWriterTest_1, WithFullDB) {
	void test() {		
		INote *note = new Note(1);
		IUser *result = note->getWriter();
		
		assertEquals("solovev", result->getLogin());
				
		delete note;
		delete result;
	}
} TEST_END;

TEST_from(GetWriterTest_2, WithFullDB) {
	void test() {		
		INote *note = new Note(2);
		IUser *result = note->getWriter();
		
		assertEquals("grosheva", result->getLogin());
				
		delete note;
		delete result;
	}
} TEST_END;

TEST_from(GetTextTest_1, WithFullDB) {
	void test() {		
		INote *note = new Note(1);
		std::string result = note->getText();
		
		assertEquals("unknown exception", result);
				
		delete note;
	}
} TEST_END;

TEST_from(GetTextTest_2, WithFullDB) {
	void test() {		
		INote *note = new Note(2);
		std::string result = note->getText();
		
		assertEquals("need more info", result);
				
		delete note;
	}
} TEST_END;

TEST_from(GetAttachmentsTest_IsNotEmpty, WithFullDB) {
	void test() {		
		INote *note = new Note(3);
		std::vector<IAttachment *> result = note->getAttachments();
		
		assertEquals("documentation.txt", result[0]->getFileName());
				
		int n = result.size();
		for(int i = 0; i < n; i++) {
			delete result[i];
		}

		delete note;
	}
} TEST_END;

TEST_from(GetAttachmentsTest_IsEmpty, WithFullDB) {
	void test() {		
		INote *note = new Note(1);
		std::vector<IAttachment *> result = note->getAttachments();
		
		assertEquals(true, result.empty());
				
		delete note;
	}
} TEST_END;

TEST_from(NoteConstructorTest, WithFullDB) {
	void test() {	
		IUser *user = new User(1);
		INote *note = new Note(*user, "Text Note");
		
		IUser *curUser = note->getWriter();

		assertEquals("Text Note", note->getText());
		assertEquals(user->getName(), curUser->getName());
				
		delete curUser;
		delete user;
		delete note;
	}
} TEST_END;

TEST_from(AddAttachmentTest, WithFullDB) {
	void test() {	
		INote *note = new Note(1);
		IUser *user = new User(2);
		IAttachment *attach = new Attachment("document.txt", "descript", *user); 		

		note->add(*attach);

		std::vector<class IAttachment *> result = note->getAttachments();
		IAttachment *curAttach;
		int len = result.size();
		bool haveAttach = false;

		for(int i = 0; i < len; i++) {
			curAttach = result[i];
			
			if(attach->getFileName() == curAttach->getFileName()) {
				haveAttach = true;
			}
			
			delete curAttach;
		}
		
		assertTrue(haveAttach);
		
		delete note;
		delete user;
		delete attach;
	}
} TEST_END;

#endif


#ifdef COMPILE_WITH_TESTS
#include "test_WithFullDB.h"

#include "Attachment.h"
#include "User.h"
#include "Note.h"


TEST_from(GetWriterTest, WithFullDB) {
	void test() {		
		INote *note = new Note();
		IUser *result = note->getWriter();
		
		assertEquals("solovev", result->getLogin());
				
		delete note;
		delete result;
	}
} TEST_END;


#endif


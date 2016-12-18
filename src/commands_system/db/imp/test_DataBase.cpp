#ifdef COMPILE_WITH_TESTS

#include "../Select.h"
#include "../Insert.h"
#include "../Delete.h"
#include "../Update.h"
#include "../../utils/Test.h"
#include "../../utils/Assertions.h"
#include "DataBase.h"
#include "../ITable.h"
#include "../DataBaseException.h"

using namespace std;

TEST (CanCreateDB) {
	void test() {
		DataBase();
	}
}TEST_END;

TEST (CanCreateDBAsIDBPointer) {
	void test() {
	  DataBase _db(TESTONLY);
	  IDataBase *db = &_db;
		db->open();
		db->close();
		(*db).open();
		(*db).close();
	}
}TEST_END;

TEST (CanCreateDBAsIDB) {
	void test() {
	  DataBase _db(TESTONLY);
	  IDataBase &db = _db;
		db.open();
		db.close();
	}
}TEST_END;



TEST_abstract (WithDB) {
  IDataBase *db;
	void before() {
	  DataBase *_db = new DataBase(TESTONLY);
		db = _db;
		db->open();
	}
	void after() {
		db->close();
		delete db;
	}
};



TEST_from(CanSelectAllColumns, WithDB) {
	void test() {
	  static const char * const _cols[5] = {"id", "name", "login", "password", "type_id"};
	  vector <string> all_columns(_cols, _cols + 5);
	  Select select = Select(all_columns).from("test").where("id", 1);

	  const ITable *t = db->perform(select);

		assertEquals(1, t->getRowCount());
		assertEquals(5, t->getColCount());

		assertEquals(1, (int)t->get(0,0));
		assertEquals("Соловьев Дмитрий", (string)t->get(0,1));
		assertEquals("solovev", (string)t->get(0,2));
		assertEquals("root", (string)t->get(0,3));
		assertEquals(1, (int)t->get(0,4));

		delete t;
	}
}TEST_END;



TEST_from(CanSelectSomeColumnsUsingWhere, WithDB) {
	void test() {
	  static const char * const _cols[3] = {"name", "login", "type_id"};
	  vector <string> some_columns(_cols, _cols + 3);
	  Select select = Select(some_columns).from("test").where("id", 4);

	  const ITable *t = db->perform(select);

		assertEquals(1, t->getRowCount());
		assertEquals(3, t->getColCount());

		assertEquals("Волков Денис", (string)t->get(0,0));
		assertEquals("volkov", (string)t->get(0,1));
		assertEquals(3, (int)t->get(0,2));

		delete t;
	}
}TEST_END;



TEST_from(CanSelectSomeColumnsNotUsingWhere, WithDB) {
	void test() {
	  static const char * const _cols[3] = {"name", "login", "type_id"};
	  vector <string> some_columns(_cols, _cols + 3);
	  Select select = Select(some_columns).from("test");

	  const ITable *t = db->perform(select);

		assertEquals(4, t->getRowCount());
		assertEquals(3, t->getColCount());

		assertEquals("Волков Денис", (string)t->get(3,0));
		assertEquals("volkov", (string)t->get(3,1));
		assertEquals(3, (int)t->get(3,2));

		delete t;
	}
}TEST_END;




TEST_from(CanPerformTwoSelects, WithDB) {
	void test() {
	  static const char * const _cols[3] = {"name", "login", "type_id"};
	  vector <string> some_columns(_cols, _cols + 3);
	  Select select = Select(some_columns).from("test").where("id", 4);
	
		delete db->perform(select);
		delete db->perform(select);
	}
} TEST_END;





TEST_from(CanDelete, WithDB) {
	void test() {
	  Delete del = Delete().from("test").where("id", 4);
	  Select sel1 = Select(vector<string>(1, "id")).from("test").where("id", 1);
	  Select sel2 = Select(vector<string>(1, "id")).from("test").where("id", 2);
	  Select sel3 = Select(vector<string>(1, "id")).from("test").where("id", 3);
	  Select sel4 = Select(vector<string>(1, "id")).from("test").where("id", 4);
	  const ITable *t;

		t = db->perform(del);
		assertEquals((const ITable *)nullptr, t);
		
		t = db->perform(sel1);
		assertEquals(1, t->getRowCount());
		assertEquals(1, t->getColCount());
		delete t;

		t = db->perform(sel2);
		assertEquals(1, t->getRowCount());
		assertEquals(1, t->getColCount());
		delete t;

		t = db->perform(sel3);
		assertEquals(1, t->getRowCount());
		assertEquals(1, t->getColCount());
		delete t;

		t = db->perform(sel4);
		assertEquals(0, t->getRowCount());
		assertEquals(0, t->getColCount());
		delete t;
	}
} TEST_END;




TEST_exception_from(CannotInsertWithID, DataBaseException, WithDB) {
	void test() {
	  static const char * const _cols[] = {"id", "name", "login", "password", "type_id"};
	  vector<string> columns(_cols, _cols + sizeof _cols/sizeof*_cols);
	  const Element _vals[] = {10000, "Brad Pitt", "braddy", "mudak", 55555};
	  vector<Element> values(_vals, _vals + sizeof _vals/sizeof*_vals);
		Insert insert = Insert().into("test", columns).values(values);

		db->perform(insert);
	}
} TEST_END;


TEST_from(CanInsert, WithDB) {
	void test() {
	  static const char * const _cols[] = {"name", "login", "password", "type_id"};
	  vector<string> columns(_cols, _cols + sizeof _cols/sizeof*_cols);
	  const Element _vals[] = {"Brad Pitt", "braddy", "mudak", 55555};
	  vector<Element> values(_vals, _vals + sizeof _vals/sizeof*_vals);
		Insert insert = Insert().into("test", columns).values(values);

		const ITable * table = db->perform(insert);
		delete table;
	}
} TEST_END;


TEST_exception_from(CannotInsertPartial, DataBaseException, WithDB) {
	void test() {
	  static const char * const _cols[] = {"name", "login", "type_id"};
	  vector<string> columns(_cols, _cols + sizeof _cols/sizeof*_cols);
	  const Element _vals[] = {"Brad Pitt", "braddy", 55555};
	  vector<Element> values(_vals, _vals + sizeof _vals/sizeof*_vals);
		Insert insert = Insert().into("test", columns).values(values);

		assertEquals((const ITable *)nullptr, db->perform(insert));
	}
} TEST_END;




typedef pair<string, Element> SET_TO;

TEST_from(CanUpdate, WithDB) {
	void test() {
	  const SET_TO set_to[] = {
		  SET_TO("login", "new login"),
		  SET_TO("password", "12345"),
		  SET_TO("type_id", 2)
	  };
	  const vector<SET_TO> a(set_to, set_to + 3);
	  Update update = Update("test").set(a).where("id", 1);

		assertEquals((const ITable *)nullptr, db->perform(update));



	  static const char * const _cols[5] = {"id", "name", "login", "password", "type_id"};
	  vector <string> all_columns(_cols, _cols + 5);
	  Select select = Select(all_columns).from("test").where("id", 1);

	  const ITable *t = db->perform(select);

		assertEquals(1, t->getRowCount());
		assertEquals(5, t->getColCount());

		assertEquals(1, (int)t->get(0,0));
		assertEquals("Соловьев Дмитрий", (string)t->get(0,1));
		assertEquals("new login", (string)t->get(0,2));
		assertEquals("12345", (string)t->get(0,3));
		assertEquals(2, (int)t->get(0,4));

		delete t;
	}
} TEST_END;



#endif


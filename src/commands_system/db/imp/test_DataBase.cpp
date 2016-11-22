#include "../Select.h"
#include "../Insert.h"
#include "../Delete.h"
#include "../../utils/Test.h"
#include "../../utils/Assertions.h"
#include "DataBase.h"
#include "../ITable.h"

using namespace std;

TEST (CanCreateDB) {
	void test() {
		DataBase();
	}
}TEST_END;

TEST (CanCreateDBAsIDBPointer) {
	void test() {
	  DataBase _db;
	  IDataBase *db = &_db;
		db->open();
		db->close();
		(*db).open();
		(*db).close();
	}
}TEST_END;

TEST (CanCreateDBAsIDB) {
	void test() {
	  DataBase _db;
	  IDataBase &db = _db;
		db.open();
		db.close();
	}
}TEST_END;



TEST_abstract (WithDB) {
  IDataBase *db;
	void before() {
	  DataBase *_db = new DataBase();
		db = _db;
		db->open();
		_db->__add_test();
	}
	void after() {
		db->close();
		delete db;
	}
};



TEST_from(CanSelectFromDB) : WithDB {
	void test() {
	  vector <string> a;
	  Select s = Select(a).from("test").where("id", 1);
	  const ITable &t = db->perform(s);
		assertEquals(1, t.getRowCount());
		assertEquals(5, t.getColCount());
		//1	—оловьев\x20ƒмитрий	solovev		root		1
		//delete &t;
	}
}TEST_END;



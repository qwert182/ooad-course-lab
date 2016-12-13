#ifdef COMPILE_WITH_TESTS

#include "test_WithFullDB.h"

#include "../../db/imp/DataBase.h"
#include "../../db/instance.h"

void WithFullDB::before() {
	DataBase::CreateTestInstance();
	dataBase->open();
}

void WithFullDB::after() {
	delete dataBase;
	dataBase = nullptr;
}

#endif


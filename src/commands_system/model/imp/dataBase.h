#pragma once

// база данных
#include "../../db/IDataBase.h"

// бросает при ошибке
#include "../../db/DataBaseException.h"




// возвращает при выполнении запроса таблицу
#include "../../db/ITable.h"
// дл€ удобства
#include <memory>
class ptrTable : public std::unique_ptr<const ITable> {
public:
	ptrTable(const ITable *p) : std::unique_ptr<const ITable>(p) {}
};




// таблица состоит из элементов (либо int, либо string)
#include "../../db/Element.h"

// бросает при несовпадении типов
#include "../../db/WrongTypeException.h"





// запросы

// пока хватит Select'а (дл€ get* функций)
#include "../../db/Select.h"
// дл€ удобства
#define SELECT(columns) (Select(std::vector<std::string>((columns), &(columns)[sizeof(columns)/sizeof(*(columns))])))
#define SELECT_ONLY(one_column) (Select(std::vector<std::string>(1, one_column)))

#include "../../db/Update.h"
#define SET_ONLY(column, value) set(std::vector<std::pair<std::string, Element> >(1, std::pair<std::string, Element>((column), (value))))

#include "../../db/Insert.h"
#define INTO(table, columns) into((table), std::vector<std::string> ((columns), (columns) + sizeof (columns)/sizeof*(columns)))
#define VALUES(vals) values(std::vector<Element> ((vals), (vals) + sizeof (vals)/sizeof*(vals)))




// экземпл€р базы данных (выполн€ем запросы через него)
#include "../../db/instance.h"


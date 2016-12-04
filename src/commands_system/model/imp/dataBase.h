#pragma once

// база данных
#include "../../db/IDataBase.h"

// бросает при ошибке
#include "../../db/DataBaseException.h"


// возвращает при выполнении запроса таблицу
#include "../../db/ITable.h"


// таблица состоит из элементов (либо int, либо string)
#include "../../db/Element.h"

// бросает при несовпадении типов
#include "../../db/WrongTypeException.h"




// запросы

// пока хватит Select'а (дл€ get* функций)
#include "../../db/Select.h"






// экземпл€р базы данных (выполн€ем запросы через него)


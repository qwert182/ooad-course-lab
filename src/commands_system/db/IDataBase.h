#pragma once

//Назначение:
//	Используется для выполнения запросов.
//Использование:
//	При выполнении операций в случае ошибки бросает DataBaseException.
//	НЕОБХОДИМО УДАЛЯТЬ ITable * С ПОМОЩЬЮ delete.
class IDataBase {
public:
	virtual void open() = 0;
	virtual void close() = 0;
	virtual const class ITable * perform(const class IQuery &query) = 0;
	virtual ~IDataBase() {}
};


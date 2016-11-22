#pragma once

#include "../utils/Exception.h"


//Ќазначение:
//	Ѕросаетс€ при несоответствии типов данных в методах класса Element:
//	- приведение к целому: operator int;
//	- приведение к строке: operator string;
//	- сравнение: operator ==.
//»спользование:
//	Element e = 100;
//	try {
//		int i = e; // OK
//		string s = e; // throw WrongTypeException
//	} catch (WrongTypeException e) {
//		std::cerr << e.what(); // "Element doesn't contain <string>"
//	}
class WrongTypeException : public Exception {
public:
	WrongTypeException(const char *what) : Exception(what) {}
};


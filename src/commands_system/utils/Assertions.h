#pragma once

#include "AssertionFailedException.h"



template <typename T>
void assertEqual(const T &expected, const T &actual, const char *str) {
	if (actual != expected) {
		throw AssertionFailedException(str);
	}
}



template <typename T>
void assertNotEqual(const T &expected, const T &actual, const char *str) {
	if (actual == expected) {
		throw AssertionFailedException(str);
	}
}



void __inline assertTrue(bool condition, const char *str) {
	if (!condition) {
		throw AssertionFailedException(str);
	}
}





#define assertEqual(expected, actual) assertEqual((expected), (actual), #expected " != " #actual)
#define assertNotEqual(expected, actual) assertNotEqual((expected), (actual), #expected " == " #actual)




#define assertTrue(cond) assertTrue((cond), #cond "is not True")
#define assertFalse(cond) assertTrue(!(cond), #cond "is not False")



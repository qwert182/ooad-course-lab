#pragma once

#include "AssertionFailedException.h"
#include <sstream>
#include <string>


template <typename T>
void _assertThrowExceptionWithMessage(const T &expected, const T &actual, const char *str) {
	std::ostringstream ss;
	ss << "\n\n\t" << str << "\n\n\t";
	ss << "expected: " << expected << "\n\t";
	ss << "actual: " << actual << '\n';
	throw AssertionFailedException(ss.str().c_str());
}



template <typename T>
void assertEquals(const T &expected, const T &actual, const char *str) {
	if (actual != expected) {
		_assertThrowExceptionWithMessage(expected, actual, str);
	}
}

template <typename T>
void assertNotEquals(const T &expected, const T &actual, const char *str) {
	if (actual == expected) {
		_assertThrowExceptionWithMessage(expected, actual, str);
	}
}




void __inline assertEquals(const char expected[], const std::string &actual, const char *str) {
	if (actual != expected) {
		_assertThrowExceptionWithMessage(std::string(expected), actual, str);
	}
}

void __inline assertNotEquals(const char expected[], const std::string &actual, const char *str) {
	if (actual == expected) {
		_assertThrowExceptionWithMessage(std::string(expected), actual, str);
	}
}




void __inline assertTrue(bool condition, const char *str) {
	if (!condition) {
		throw AssertionFailedException(str);
	}
}

void __inline assertFalse(bool condition, const char *str) {
	if (condition) {
		throw AssertionFailedException(str);
	}
}



#define assertEquals(expected, actual) \
	assertEquals((expected), (actual), "assertEquals(" #expected ", " #actual ")")

#define assertNotEquals(expected, actual) \
	assertNotEquals((expected), (actual), "assertNotEquals(" #expected ", " #actual ")")

#define assertTrue(cond) \
	assertTrue((cond), "\n\n\tassertTrue(" #cond ")\n\n\t" #cond " is False\n")

#define assertFalse(cond) \
	assertFalse((cond), "\n\n\tassertFalse(" #cond ")\n\n\t" #cond " is True\n")


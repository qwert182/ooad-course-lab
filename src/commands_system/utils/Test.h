#pragma once

#ifdef COMPILE_WITH_TESTS



class Test {
public:
	static void All();

protected:
	virtual void do_test();

	virtual void before();
	virtual void test() = 0;
	virtual void after();

	Test();

private:
	static void All_inner(void *);
protected:
	// for ExceptionTest
	static void throw_no_exception();
};





template <class E>
class ExceptionTest : public Test {
protected:
	virtual void do_test() {
	  bool ok = false;
		try {
			test();
		} catch (E) {
			ok = true;
		}
		if (!ok) throw_no_exception();
	}
};






#define TEST(name) static struct name : public Test
#define TEST_from(name) static struct name
#define TEST_abstract(name) struct name : public Test
#define TEST_exception(name, exception) static struct name : public ExceptionTest<exception>
#define TEST_abstract_exception(name, exception) struct name : public ExceptionTest<exception>

#define __TEST_END(line) test_at_line_##line
#define _TEST_END(line) __TEST_END(line)
#define TEST_END _TEST_END(__LINE__)



#else




#define TEST(name) class name
#define TEST_from(name) class name
#define TEST_abstract(name) class name
#define TEST_exception(name, exception) class name

#define TEST_END




#endif


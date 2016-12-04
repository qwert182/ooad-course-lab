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





template <class E, class Base>
class ExceptionTest : public Base {
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






#define TEST(name)                                   static struct name : public Test
#define TEST_from(name, from)                        static struct name : public from
#define TEST_abstract(name)                                 struct name : public Test
#define TEST_abstract_from(name, from)                      struct name : public from
#define TEST_exception(name, exception)              static struct name : public ExceptionTest<exception, Test>
#define TEST_abstract_exception(name, exception)            struct name : public ExceptionTest<exception, Test>
#define TEST_exception_from(name, exception, from)   static struct name : public ExceptionTest<exception, from>
#define TEST_abstract_exception_from(name, exception, from) struct name : public ExceptionTest<exception, from>

#define __TEST_END(line) test_at_line_##line
#define _TEST_END(line) __TEST_END(line)
#define TEST_END _TEST_END(__LINE__)



#else




#define TEST(name)                                          struct name
#define TEST_from(name, from)                               struct name
#define TEST_abstract(name)                                 struct name
#define TEST_abstract_from(name, from)                      struct name
#define TEST_exception(name, exception)                     struct name
#define TEST_abstract_exception(name, exception)            struct name
#define TEST_exception_from(name, exception, from)          struct name
#define TEST_abstract_exception_from(name, exception, from) struct name

#define TEST_END




#endif


#ifndef UNITTEST_H
#define UNITTEST_H


#include <stdio.h>
#include <sstream>
#include <string>
#include <cmath>

// Macros definitions

#define INTERNAL_CATCH_LINESTR2( line ) #line
#define INTERNAL_CATCH_LINESTR( line ) INTERNAL_CATCH_LINESTR2( line )

#define TEST_FAILED(comment) \
	*throw_error() = UnitTestError(comment, __FILE__, INTERNAL_CATCH_LINESTR( __LINE__ ) )

#define SUCCEED() \
	(void)0

#define FAIL() \
	TEST_FAILED("An error was thrown.")

#define ASSERT_TRUE(CONDITION) \
	if (CONDITION) \
	{ \
		SUCCEED(); \
	} \
	else \
		TEST_FAILED(#CONDITION) \

#define ASSERT_FALSE(CONDITION) \
	if (!(CONDITION)) \
	{ \
		SUCCEED(); \
	} \
	else \
	TEST_FAILED(#CONDITION) \

#define ASSERT_EQ(VALUE1, VALUE2) \
	if ((VALUE1) == (VALUE2)) \
	{ \
		SUCCEED(); \
	} else \
        TEST_FAILED(#VALUE1 " != " #VALUE2 )

#define ASSERT_NE(VALUE1, VALUE2) \
	if (VALUE1 != VALUE2) \
	{ \
		SUCCEED(); \
	} else \
        TEST_FAILED(#VALUE1 " == " #VALUE2 )

#define ASSERT_LT(VALUE1, VALUE2) \
	if (VALUE1 > VALUE2) \
	{ \
		SUCCEED(); \
	} else \
        TEST_FAILED(#VALUE1 " <= " #VALUE2 )

#define ASSERT_LE(VALUE1, VALUE2) \
	if (VALUE1 >= VALUE2) \
	{ \
		SUCCEED(); \
	} else \
        TEST_FAILED(#VALUE1 " < " #VALUE2 )

#define ASSERT_GT(VALUE1, VALUE2) \
	if (VALUE1 < VALUE2) \
	{ \
		SUCCEED(); \
	} else \
        TEST_FAILED(#VALUE1 " >= " #VALUE2 )

#define ASSERT_GE(VALUE1, VALUE2) \
	if ((VALUE1) <= (VALUE2)) \
	{ \
		SUCCEED(); \
	} else \
        TEST_FAILED(#VALUE1 " > " #VALUE2 )

#define ASSERT_STREQ(VALUE1, VALUE2) \
	if ((VALUE1) == (VALUE2)) \
	{ \
		SUCCEED(); \
	} else \
        TEST_FAILED(#VALUE1 " != " #VALUE2 )

#define ASSERT_STRNE(VALUE1, VALUE2) \
	if (VALUE1 != VALUE2) \
	{ \
		SUCCEED(); \
	} else \
        TEST_FAILED(#VALUE1 " == " #VALUE2 )

#define ASSERT_NEAR(VALUE1, VALUE2, E) \
    if((fabs(VALUE1 - VALUE2))<E) { \
        SUCCEED(); \
    } else TEST_FAILED(#VALUE1 " != " #VALUE2)


#define ASSERT_FLOATEQ(VALUE1, VALUE2) \
    ASSERT_NEAR(VALUE1, VALUE2, 0.0000001)

#define ASSERT_FLOATNE(VALUE1, VALUE2) \
    if((fabs(VALUE1 - VALUE2)) > 0.0000001) { \
        SUCCEED(); \
    } else TEST_FAILED(#VALUE1 " == " #VALUE2)


#define ASSERT_DOUBLEEQ(VALUE1, VALUE2) \
    ASSERT_NEAR(VALUE1, VALUE2, 0.0000001)

#define ASSERT_DOUBLENE(VALUE1, VALUE2) \
    if((fabs(VALUE1 - VALUE2)) > 0.0000001) { \
        SUCCEED(); \
    } else TEST_FAILED(#VALUE1 " == " #VALUE2)

// Macros end

/*
 * @TESTPREFIX - name of Test case
 * @TESTNAME -
 * Defines a TEST, which declares a unit test.
 */
#define TEST(TESTPREFIX, TESTNAME) \
	class TestInfo; \
	class TESTPREFIX##TESTNAME : public UnitTestBase \
	{ \
	public: \
		TESTPREFIX##TESTNAME() \
		: UnitTestBase(#TESTPREFIX, #TESTNAME) \
		{ } \
		void run_unit_test() override; \
	private: \
		static TestInfo* test_info; \
	}; \
	TestInfo* TESTPREFIX##TESTNAME::test_info = UnitTests::RegisterTest(#TESTPREFIX, #TESTNAME, new TESTPREFIX##TESTNAME()); \
	void TESTPREFIX##TESTNAME::run_unit_test()

/*
 * Result of a unit test.
 */
enum class UnitTestResult
{
	TestNotRun,

    TestPassed,

	TestFailed,
};

/*
 * Save and print error.
 */
class UnitTestError
{
public:

    /*
     * @comments - comment about error
     * @file - file from where error
     * @line - line from where error
     */
	UnitTestError(std::string comments, const char* file, const char* line);

	// convert string_stream to string
	std::string get_error();


	inline UnitTestError& operator<<(int input)	{
		string_stream << input;
		return *this;
	}

	inline UnitTestError& operator<<(std::string input)	{
		string_stream << input;
		return *this;
	}

private:

	//
	std::stringstream string_stream;
};

class UnitTestError;
class TestInfo;
class UnitTestBase
{
public:



	// Creates a new instance of the UnitTestBase class.
	// @param test_prefix The prefix of the unit test.
	// @param test_name The name of the unit test.
	UnitTestBase(std::string test_prefix, std::string test_name);

	// Destroys this instance of the UnitTestBase class.
	virtual ~UnitTestBase();

	/*
	* Public Virtual Methods
	*/

	// Runs the unit test.
	virtual void run_unit_test() = 0;

	// return  error message.
	std::string get_error();

	// return unit test result.
	UnitTestResult get_result();

	// Runs the unit test.
	void run();


	UnitTestBase* throw_error();


	void operator=(UnitTestError stream);

private:

	std::string test_error;

	std::string test_name;

	std::string test_prefix;

	UnitTestResult test_result;
};

namespace UnitTests
{
	// @testCase - test case.
	// @testName - test name.
	TestInfo* RegisterTest(std::string testCase, std::string testName, UnitTestBase* unitTest);

	// Runs all unit tests.
	bool Run();
};

#endif

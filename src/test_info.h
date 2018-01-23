#ifndef TESTINFO_H
#define TESTINFO_H

#include <unittest/test.h>

#include <string>

// unit test information
class TestInfo
{
public:

	 // @testCase - name of the test case
	 // @testName - name of the test
	TestInfo(std::string testCase, std::string testName,
		UnitTestBase* unitTest);

	~TestInfo();

	 // return error message
	std::string get_error();

	// return unit test result
	UnitTestResult get_result();

	// return - test case name
	std::string get_test_case();

	// return - test name
	std::string get_test_name();

	// Runs the unit test
	void run();

private:

	std::string test_case;

	std::string test_name;

	UnitTestBase* unit_test;
};

#endif

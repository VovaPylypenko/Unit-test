
#include "unit_test_exception.h"

#include <unittest/test.h>
#include <iostream>

/*
 * @testPrefix - prefix of the unit test.
 * @testName - name of the unit test.
*/
UnitTestBase::UnitTestBase(std::string test_prefix, std::string test_name)
{
	this->test_prefix = test_prefix;
	this->test_name = test_name;

	test_result = UnitTestResult::TestNotRun;
}

UnitTestBase::~UnitTestBase(){}

// The error message.
std::string UnitTestBase::get_error()
{
		return test_error;
}


UnitTestResult UnitTestBase::get_result()
{
	return test_result;
}

// Runs the unit test.
void UnitTestBase::run()
{
	run_unit_test();

	// If the test result is still 'not run', test passed
	if (test_result == UnitTestResult::TestNotRun)
	{
		test_result = UnitTestResult::TestPassed;
	}
}

// Throw error if the test has failed.
UnitTestBase* UnitTestBase::throw_error()
{
	return this;
}

// @stream - stream operator.
void UnitTestBase::operator=(UnitTestError stream)
{
	test_result = UnitTestResult::TestFailed;

	test_error = stream.get_error();

	throw UnitTestException();
}

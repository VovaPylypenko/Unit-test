#include "test_info.h"
TestInfo::TestInfo(std::string test_case, std::string test_name,
	UnitTestBase* unit_test)
{
	this->test_case = test_case;
	this->test_name = test_name;
	this->unit_test = unit_test;
}

TestInfo::~TestInfo()
{
	delete unit_test;
}

std::string TestInfo::get_error()
{
	return unit_test->get_error();
}

UnitTestResult TestInfo::get_result()
{
	return unit_test->get_result();
}

std::string TestInfo::get_test_case()
{
	return test_case;
}

std::string TestInfo::get_test_name()
{
	return test_name;
}


void TestInfo::run()
{
	unit_test->run();
}


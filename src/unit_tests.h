#ifndef GLOBALUNITTESTS_H
#define GLOBALUNITTESTS_H

#include <string>

class TestInfo;
class UnitTestBase;


namespace UnitTests
{
	// @testCase - test case.
	// @testName - test name.
	TestInfo* RegisterTest(std::string testCase, std::string testName, UnitTestBase* unitTest);
};

#endif

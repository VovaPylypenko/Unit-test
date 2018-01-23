#include "unit_tests.h"
#include "test_info_compare.h"
#include <unittest/test.h>
#include <algorithm>
#include <exception>
#include <iostream>
#include <map>
#include <vector>

struct UnitTestData
{
	std::vector<TestInfo*> registered_tests;
	int test_case_count;
	TestInfoCompare test_compare;
	int test_total_count;
	std::map<std::string, int> test_total_by_case;
};

static UnitTestData* unit_test_data = nullptr;
TestInfo* UnitTests::RegisterTest(std::string testCase, std::string testName, UnitTestBase* unitTest)
{
	if (unit_test_data == nullptr)
	{
		unit_test_data = new UnitTestData();
	}

	TestInfo* testInfo = new TestInfo(testCase, testName, unitTest);

	unit_test_data->registered_tests.push_back(testInfo);

	if (unit_test_data->test_total_by_case.find(testCase) == unit_test_data->test_total_by_case.end())
	{
		unit_test_data->test_total_by_case[testCase] = 0;

		++unit_test_data->test_case_count;
	}

	++unit_test_data->test_total_count;
	++unit_test_data->test_total_by_case[testCase];

	return testInfo;
}

bool UnitTests::Run()
{
	std::cout << "Number of running tests : " << unit_test_data->test_total_count << "\nNumber of test cases :"
		<< unit_test_data->test_case_count << std::endl;
	std::cout <<"===============================================\n\n";

	int passedTestCount = 0;
	int failedTestCount = 0;
	std::vector<TestInfo*> failedTests;
	std::string previousCase = "";

	for (std::vector<TestInfo*>::iterator it = unit_test_data->registered_tests.begin();
		it != unit_test_data->registered_tests.end(); ++it)
	{
		TestInfo* testInfo = *it;

		if (previousCase != testInfo->get_test_case())
		{
			previousCase = testInfo->get_test_case();

			std::cout <<"-----------------------------------------------";
			std::cout << std::endl << "Running " << unit_test_data->test_total_by_case[previousCase]
				<< " tests from " << previousCase << " case." << std::endl;
		}

		std::cout << "[    RUN  ] Test name : " << testInfo->get_test_name() << " \n";

		try
		{
			testInfo->run();
		}
		catch (std::exception&)
		{

		}

		if (testInfo->get_result() == UnitTestResult::TestPassed)
		{
			std::cout << "[     OK  ]" << std::endl;

			++passedTestCount;
		}
		else
		{
			std::cout << "[  FAILED ]" << std::endl;
			std::cout << "Error: " << std::endl << testInfo->get_error() << std::endl;

			++failedTestCount;

			failedTests.push_back(testInfo);
		}
	}
	std::cout <<"-----------------------------------------------\n\n";

	std::cout <<"===============================================\n";
	std::cout << std::endl << "Number of run test : " << unit_test_data->test_total_count << std::endl;


	std::cout << "Number of OK test : " << passedTestCount << std::endl;

	std::cout << "Number of Failed test: " << failedTestCount << " tests" << std::endl;

	for (std::vector<TestInfo*>::iterator it = failedTests.begin();
		 it != failedTests.end(); ++it)
	{
		TestInfo* testInfo = *it;

		std::cout << "Case name : \""<< testInfo->get_test_case() << "\" - test name : \"" << testInfo->get_test_name() <<"\"\n";
	}

	std::cout <<"===============================================\n";



	// free
	for (std::vector<TestInfo*>::iterator it = unit_test_data->registered_tests.begin();
		it != unit_test_data->registered_tests.end(); ++it)
	{
		delete *it;
	}
	if (failedTestCount == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}


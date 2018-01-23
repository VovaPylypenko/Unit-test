#ifndef UNITTESTCOMPARE_H
#define UNITTESTCOMPARE_H

#include "test_info.h"


struct TestInfoCompare
{

	bool operator() (TestInfo* i, TestInfo* j)
	{
		if (i->get_test_case() < j->get_test_case())
		{
			return true;
		}
		else if (i->get_test_case() == j->get_test_case() && i->get_test_name() < j->get_test_name())
		{
			return true;
		}
		else
		{
			return false;
		}
	}
};

#endif


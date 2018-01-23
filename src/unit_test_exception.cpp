
#include "unit_test_exception.h"
UnitTestException::UnitTestException()
{
}
const char* UnitTestException::what() const throw()
{
  return "The unit test failed.";
}

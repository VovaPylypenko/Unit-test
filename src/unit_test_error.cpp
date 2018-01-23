#include <unittest/test.h>

UnitTestError::UnitTestError(std::string comments, const char* file, const char* line)
{
   string_stream << file << ':' << line << '\n' <<comments; //<< " is not true";
}

std::string UnitTestError::get_error()
{
  return string_stream.str();
}


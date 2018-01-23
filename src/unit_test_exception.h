#ifndef UNITTESTEXCEPTION_H
#define UNITTESTEXCEPTION_H

#include <exception>

class UnitTestException : public std::exception
{
  public:

   UnitTestException();

    // Returns the exception error message
   virtual const char* what() const throw();
};

#endif


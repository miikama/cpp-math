
#ifndef ERRORS_HPP
#define ERRORS_HPP

#include <exception>


class IndexOutOfBoundsException: public std::exception{
  virtual const char* what() const throw()
  {
    return "Index out of bounds";
  }
} IndexOutOfBoundsError;





#endif
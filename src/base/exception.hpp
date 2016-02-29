#ifndef _BASE_EXCEPTION_HPP
#define _BASE_EXCEPTION_HPP

#include <string>

namespace Base
{

class Exception
{
public:
    virtual const std::string what() const = 0;
};

} // namespace Base

#endif // _BASE_EXCEPTION_HPP

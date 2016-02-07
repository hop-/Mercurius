#ifndef _BASE_EXCEPTION_HPP
#define _BASE_EXCEPTION_HPP

namespace Base
{

class exception
{
public:
    virtual const std::string& what() const = 0;
};

} // namespace Base

#endif // _BASE_EXCEPTION_HPP

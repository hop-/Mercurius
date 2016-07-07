#ifndef _BASE_UTILITY_HPP_
#define _BASE_UTILITY_HPP_

namespace Base
{

class Utility
{
public:
    template<class... T>
    static void ignoreUnused(T&&...) {}
};

} // end of namespace Base

#endif // _BASE_UTILITY_HPP_

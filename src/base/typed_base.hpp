#ifndef _CORE_TYPED_BASE_HPP_
#define _CORE_TYPED_BASE_HPP_

#include <cassert>

namespace Base
{

class TypedBase
{
public:
    class ID
    {
        static int m_count;
        const int m_id;

     public:
        ID();
        operator int() const;
    };

    virtual ~TypedBase() = default;
    virtual int getType() const = 0;
};


} // namespace Base

#endif //_CORE_TYPED_BASE_HPP_

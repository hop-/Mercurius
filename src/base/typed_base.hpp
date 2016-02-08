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

    struct Less
    {
        bool operator() (TypedBase* left, TypedBase* right) const;
        typedef TypedBase* first_argument_type;
        typedef TypedBase* second_argument_type;
        typedef bool result_type;
    };

    virtual ~TypedBase() = default;
    virtual int getType() const = 0;

protected:
    virtual bool less(TypedBase* object) = 0;
};


} // namespace Base

#endif //_CORE_TYPED_BASE_HPP_

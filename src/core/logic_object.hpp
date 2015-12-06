#ifndef _LOGIC_OBJECT_HPP_
#define _LOGIC_OBJECT_HPP_

#include "subject.hpp"
#include "shape.hpp"
#include "position.hpp"

namespace Core
{

class LogicObject :
    public Subject
{
    Shape m_shape;
    Position m_position;

protected:
    LogicObject() = default;

public:
    virtual ~LogicObject() = default;
};

} // namespace Core

#endif //_LOGIC_OBJECT_HPP_

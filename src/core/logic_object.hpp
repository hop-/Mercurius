#ifndef _CORE_LOGIC_OBJECT_HPP_
#define _CORE_LOGIC_OBJECT_HPP_

#include "subject.hpp"
#include "shape.hpp"
#include "position.hpp"

namespace Core
{

class LogicObject
    : public Subject
{
    Shape m_shape;
    Position m_position;

protected:
    LogicObject() = default;

public:
    virtual ~LogicObject() = default;
    void setShape(Shape shape);
    void setPosition(Position position);
    Shape shape();
    Position position();
};

} // namespace Core

#endif //_CORE_LOGIC_OBJECT_HPP_

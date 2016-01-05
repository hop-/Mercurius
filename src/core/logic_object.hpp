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

    inline void setShape(const Shape& shape)
    {
        m_shape = shape;
    }
    
    inline void setPosition(const Position& position)
    {
        m_position = position;
    }
    
    inline const Shape& shape() const
    {
        return m_shape;
    }

    inline const Position position() const
    {
        return m_position;
    }
};

} // namespace Core

#endif //_CORE_LOGIC_OBJECT_HPP_

#ifndef _CORE_DYNAMIC_OBJECT_HPP_
#define _CORE_DYNAMIC_OBJECT_HPP_

#include "logic_object.hpp"

namespace Core
{

class DynamicObject
    : public LogicObject
{
    Vector m_velocity;

public:
    void addVector(Vector vector);
};

} // namespace Core

#endif //_CORE_DYNAMIC_OBJECT_HPP_

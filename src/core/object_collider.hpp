#ifndef _CORE_OBJECT_COLLIDER_HPP_
#define _CORE_OBJECT_COLLIDER_HPP_

#include "rectangle.hpp"
#include "position.hpp"
#include "quad_tree.hpp"

#include <list>

namespace Core
{

class LogicObject;

class ObjectCollider
{
    using Objects = std::list<LogicObject*>;

    QuadTree m_quadTree;

public:
    ObjectCollider();
    ObjectCollider(Rectangle bounds);

public:
    void setBounds(Rectangle bounds);
    void insert(const LogicObject* object);
    void update(LogicObject* object, Position p);
    void remove(const LogicObject* object);
};

} // namespace Core

#endif //_CORE_OBJECT_COLLIDER_HPP_

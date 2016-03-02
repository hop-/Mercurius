#ifndef _CORE_LOGIC_HPP_
#define _CORE_LOGIC_HPP_

#include "logic_object.hpp"

#include <base/container_object.hpp>

#include <cassert>
#include <vector>

namespace Core
{

class Layer;

class Logic
    : public Base::ContainerObject<LogicObject>
{
public:
    Logic();
    virtual ~Logic();
    virtual void update();
    virtual void initObject()
    {}
};

} // namespace Core

#endif //_CORE_LOGIC_HPP_

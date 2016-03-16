#ifndef _CORE_LOGIC_HPP_
#define _CORE_LOGIC_HPP_

#include "logic_object.hpp"
#include "components.hpp"

#include <base/container_object.hpp>

#include <vector>

namespace Core
{

class Layer;
class ViewPort;

class Logic
    : public Base::ContainerObject<LogicObject>
{
    LogicObject* m_viewPort;
public:
    Logic();
    virtual ~Logic();
    virtual void update();
    virtual void initObject(){}
    void aimTo(LogicObject* l);
    const LogicObject* viewPort() const;
    const ViewPort* viewPortComponent() const;

private:
    void createViewPortObject();
};

} // namespace Core

#endif //_CORE_LOGIC_HPP_

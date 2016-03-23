#ifndef _CORE_LOGIC_HPP_
#define _CORE_LOGIC_HPP_

#include "logic_object.hpp"
#include "components.hpp"
#include "natural_power.hpp"
#include "sweep_line.hpp"

#include <base/container_object.hpp>

#include <vector>

namespace Core
{

class Layer;
class ViewPort;

class Logic
    : public Base::ContainerObject<LogicObject>
    , public Base::ContainerObject<NaturalPower>
{
    LogicObject* m_viewPort;
    SweepLine m_sweepLine;

    typedef Base::ContainerObject<LogicObject> LogicObjects;
    typedef Base::ContainerObject<NaturalPower> Powers;

public:
    Logic();
    virtual ~Logic();
    virtual void update();
    virtual void init() final;
    virtual void initObject(){}
    void aimTo(LogicObject* l);
    const LogicObject* viewPort() const;
    const ViewPort* viewPortComponent() const;
    void addToViewPort(LogicObject* object);
    void updateSweepLine(const LogicObject* object);
    bool addLogicObject(LogicObject* object);

private:
    void createViewPortObject();
    virtual void onObjectAdding(LogicObject* object);
};

} // namespace Core

#endif //_CORE_LOGIC_HPP_

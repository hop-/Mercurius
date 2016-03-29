#ifndef _CORE_LOGIC_HPP_
#define _CORE_LOGIC_HPP_

#include "logic_object.hpp"
#include "components.hpp"
#include "natural_power.hpp"
#include "object_collider.hpp"

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
    LogicObject* m_viewPort = 0;
    ObjectCollider m_collider;

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
    void updateObject(LogicObject* object, Position p);
    bool addLogicObject(LogicObject* object);

private:
    Logic(const Logic&) = delete;
    Logic& operator=(const Logic&) = delete;

private:
    void applyPowers();
    void processEvents();
    void updateLogicObjects();
    void createViewPortObject();
    virtual void onObjectAdding(const LogicObject* object);
};

} // namespace Core

#endif //_CORE_LOGIC_HPP_

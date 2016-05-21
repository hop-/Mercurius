#ifndef _ASSETS_COMPONENTS_HPP_
#define _ASSETS_COMPONENTS_HPP_

#include <core/logic_object.hpp>

#include <base/object.hpp>

namespace Base
{

class Event;

}

namespace Assets
{

class LadderZone
    : public Core::LogicObject::ComponentCreator<LadderZone>
    , public Base::Object
{
public:
    LadderZone();

    void init() {}

private:
    void onObjectCollision(Base::Event* e);
};

class DoorZone
    : public Core::LogicObject::ComponentCreator<DoorZone>
    , public Base::Object
{
public:
    DoorZone();
    void init() {}

private:
    void onObjectCollision(Base::Event* e);
};

class SwitchZone
    : public Core::LogicObject::ComponentCreator<SwitchZone>
    , public Base::Object
{
public:
    SwitchZone();
    void init() {}

private:
    void onObjectCollision(Base::Event* e);
};

} // namespace Assets

#endif //_ASSETS_COMPONENTS_HPP_

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

class PlatformZone
    : public Core::LogicObject::ComponentCreator<PlatformZone>
    , public Base::Object
{
public:
    PlatformZone();
    void init() {}

    Core::LogicObject* parent()
    {
        return Component::parent();
    }

private:
    void makeTrigger(Base::Event* e);
};

class CameraFollower
    : public Core::LogicObject::ComponentCreator<CameraFollower>
{
    int m_velocityScaleX = 1;
    int m_velocityScaleY = 1;
    Core::Position m_viewPortLastPosition = Core::Position();

public:
    void onNotify() override;
    void init();

    inline void setVelocityScale(int sx, int sy)
    {
        m_velocityScaleX = sx;
        m_velocityScaleY = sy;
    }

private:
    void move(Core::Position p);
};

} // namespace Assets

#endif //_ASSETS_COMPONENTS_HPP_

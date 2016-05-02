#ifndef _ASSETS_EVENT_GENERATOR_HPP_
#define _ASSETS_EVENT_GENERATOR_HPP_

#include <base/object.hpp>

#include <map>
#include <list>

namespace Base
{

class Event;

} // namespace Base

namespace Core
{

class LogicObject;

} // namespace Core

namespace Assets
{

class EventGenerator
    : public Base::Object
{
public:
    using Grounds = std::list<const Core::LogicObject*>;
    using GroundsOfObject = std::map<const Core::LogicObject*, Grounds>;

private:
    static GroundsOfObject m_groundsOfObject;

public:
    ~EventGenerator();

public:
    void init();

private:
    void ObjColl2OnSurface(Base::Event* e);
    void ObjColl2OnAir(Base::Event* e);
    void ObjColl2LadderEvents(Base::Event* e);
};

} // namespace Assets

#endif //_ASSETS_EVENT_GENERATOR_HPP_

#ifndef _ASSETS_EVENT_GENERATOR_HPP_
#define _ASSETS_EVENT_GENERATOR_HPP_

#include <map>
#include <list>

namespace Core
{

class Event;
class LogicObject;

} // namespace Core

namespace Assets
{

class EventGenerator
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
    void ObjColl2OnSurface(Core::Event* e);
    void ObjColl2OnAir(Core::Event* e);
};

} // namespace Assets

#endif //_ASSETS_EVENT_GENERATOR_HPP_

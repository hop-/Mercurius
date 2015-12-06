#ifndef _CORE_EVENT_GENERATOR_HPP_
#define _CORE_EVENT_GENERATOR_HPP_

namespace Core
{

class Event;
class Layer;
class Command;

class EventGenerator
{
    Event* m_catchedEvent;

public:
    EventGenerator();
    virtual ~EventGenerator() = default;
   
public:
    virtual void catchEvent() = 0;
    virtual unsigned getTicks() = 0;
    Event* getEvent();
    Command* getCommand(Layer*);
	
protected:
    void setCatchedEvent(Event*);
};

} // namespace Core

#endif //_CORE_EVENT_GENERATOR_HPP_

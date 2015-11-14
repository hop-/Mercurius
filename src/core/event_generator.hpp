#ifndef _EVENT_GENERATOR_HPP_
#define _EVENT_GENERATOR_HPP_

namespace Core
{

class Event;
class Layer;
class Command;

class EventGenerator
{
    Event* m_catchedEvent;

public:
    virtual ~EventGenerator() = default;
    virtual void catchEvent() = 0;
    virtual unsigned getTicks() = 0;
    Event* getEvent();
    Command* getCommand(Layer*);
};

} /// namespace Core

#endif //_EVENT_GENERATOR_HPP_

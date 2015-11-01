#ifndef _EVENT_GENERATOR_HPP_
#define _EVENT_GENERATOR_HPP_

namespace Core
{

class Event;
class Layer;
class Command;

class EventGenerator
{
public:
    virtual ~EventGenerator() = default;
    virtual void catchEvent() = 0;
    virtual unsigned getTicks();
    Event* getEvent();
    Command* getCommand(Layer*);
};

} /// namespace Core

#endif //_EVENT_GENERATOR_HPP_

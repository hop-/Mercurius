#ifndef _CONTROLS_HPP_
#define _CONTROLS_HPP_

#include <map>

namespace Core
{

class Command;
class Event;

class Controls
{
    std::map<Event*, Command*> m_controlMap;

public:
    void add(Event* event, Command* command);
    void remove(Event* event);
    Command* getCommand(Event* event);
};

} /// namespace Core

#endif //_CONTROLS_HPP_

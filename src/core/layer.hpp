#ifndef _CORE_LAYER_HPP_
#define _CORE_LAYER_HPP_

#include "controls.hpp"

namespace Core
{

class Gui;
class Logic;
class Event;
class Frame;
class Command;

class Layer
{
	Gui* m_gui;
    Logic* m_logic;
    Controls m_controls;
    bool m_stopped;
    bool m_hidden;
    bool m_ignoreEvent;

public:
    Layer();
    Layer(Gui* gui, Logic* logic, Controls controls,
            bool stopped = false, 
            bool hidden = false, 
            bool ignoreEvents = false);
    void changeControls(Controls controls);
    Controls getControls();
    Command* getCommand(Event* event);
    bool processEvent(Event*);
    void stop(bool stop);
    void hide(bool hide);
    void ignoreEvents(bool ingoreEvents);
    bool isStopped();
    void update();
    void draw(Frame* frame);
};

} // namespace Core

#endif //_CORE_LAYER_HPP_

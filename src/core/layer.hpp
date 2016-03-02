#ifndef _CORE_LAYER_HPP_
#define _CORE_LAYER_HPP_

#include "controls.hpp"

#include <base/object.hpp>

namespace Core
{

class Gui;
class Logic;
class Event;
class Frame;
class Command;

class Layer
    : public Base::Object
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

    inline const Controls& controls() const
    {
        return m_controls;
    }
    
    inline void stop(bool stop)
    {
        m_stopped = stop;
    }
    
    inline void hide(bool hide)
    {
        m_hidden = hide;
    }
    
    inline void ignoreEvents(bool ignoreEvents)
    {
        m_ignoreEvent = ignoreEvents;
    }
    
    inline bool isStopped() const
    {
        return m_stopped;
    }
    
    inline Gui* gui()
    {
        return m_gui;
    }

    virtual void init();

    void changeControls(Controls controls);
    Command* getCommand(Event* event);
    bool processEvent(Event*);
    void update();
    void draw();
};

} // namespace Core

#endif //_CORE_LAYER_HPP_

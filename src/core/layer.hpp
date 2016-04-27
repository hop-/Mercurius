#ifndef _CORE_LAYER_HPP_
#define _CORE_LAYER_HPP_

#include <base/container_object.hpp>

namespace Core
{

class Gui;
class GuiObject;
class Logic;
class LogicObject;
class Event;
class Frame;
class Command;

class Layer
    : public Base::ContainerObject<Base::Object>
{
	Gui* m_gui;
    Logic* m_logic;
    bool m_stopped;
    bool m_hidden;
    bool m_ignoreEvent;

public:
    Layer();
    Layer(Gui* gui, Logic* logic,
            bool stopped = false,
            bool hidden = false,
            bool ignoreEvents = false);
    virtual ~Layer();

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

    bool addGuiObject(GuiObject*);
    bool addLogicObject(LogicObject*);
    void aimTo(LogicObject*);

    virtual void initObjectPost();

    Command* getCommand(Event* event);
    bool processEvent(Event*);
    void update();
    void draw();

private:
    Layer(const Layer&) = delete;
    Layer& operator=(const Layer&) = delete;
};

} // namespace Core

#endif //_CORE_LAYER_HPP_

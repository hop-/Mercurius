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
    unsigned m_id;

public:
    Layer(Gui* gui, Logic* logic,
            bool stopped = false,
            bool hidden = false,
            bool ignoreEvents = false);

    virtual ~Layer();

public:
    static unsigned maxId();
    unsigned id() const;
    void stop(bool stop);
    void hide(bool hide);
    void ignoreEvents(bool ignoreEvents);
    bool isStopped() const;
    const Logic* logic() const;
    Gui* gui();
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

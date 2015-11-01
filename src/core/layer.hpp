#ifndef _LAYER_HPP_
#define _LAYER_HPP_

namespace Core
{

class Gui;
class Logic;
class Event;
class Frame;

class Layer
{
	Gui* m_gui;
    Logic* m_logic;
    bool m_stopped;

public:
    Layer();
    Layer(Gui* gui, Logic* logic);
    void init(Gui* gui, Logic* logic);
    bool processEvent(Event*);
    void stop(bool stop);
    void hide(bool hide);
    void ignoreEvents(bool ingoreEvents);
    bool isStopped();
    void update();
    void draw(Frame* frame);
};

} // namespace Core

#endif //_LAYER_HPP_

#ifndef _LAYER_HPP_
#define _LAYER_HPP_

namespace Core
{

class Gui;
class Logic;
class Event;

class Layer
{
	Gui* m_gui;
    Logic* m_logic;

public:
    Layer();
    Layer(Gui* gui, Logic* logic);
    void init(Gui* gui, Logic* logic);
    bool processEvent(Event*);
    void update();
};

} // namespace Core

#endif //_LAYER_HPP_

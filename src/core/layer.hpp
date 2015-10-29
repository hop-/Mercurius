#ifndef _LAYER_HPP_
#define _LAYER_HPP_

namespace Core
{

class Gui;
class Logic;
class Event;

class Layer
{
    Core::Gui* m_gui;
    Core::Logic* m_logic;

public:
    Layer();
    Layer(Core::Gui* gui, Core::Logic* logic);
    void init(Core::Gui* gui, Core::Logic* logic);
    bool processEvent(Core::Event*);
    void update();
};

} /// namespace Core

#endif //_LAYER_HPP_

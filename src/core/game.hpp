#ifndef _GAME_HPP_
#define _GAME_HPP_

#include <vector>

namespace Core
{

class Frame;
class EventGenerator;
class Layer;

class Game
{
    Frame* m_frame;
    EventGenerator* m_eventGenerator;
    std::vector<Layer*> m_layers;

public:
    void start();
    void pushLayer(Layer* layer);
    void popLayer();

private:
    void mainLoop();
};

} // namespace core

#endif //_GAME_HPP_

#ifndef _CORE_GAME_HPP_
#define _CORE_GAME_HPP_

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
    Game();
    ~Game();

public:
    void start();
    void pushLayer(Layer* layer);
    void popLayer();

private:
    void mainLoop();
};

} // namespace core

#endif //_CORE_GAME_HPP_

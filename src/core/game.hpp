#ifndef _CORE_GAME_HPP_
#define _CORE_GAME_HPP_

#include <vector>

namespace Core
{

class Frame;
class EventManager;
class Layer;

class Game
{
    Frame* m_frame;
    EventManager* m_eventManager;
    std::vector<Layer*> m_layers;

public:
    Game(Frame* frame, EventManager* eventManager);
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

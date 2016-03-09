#ifndef _CORE_GAME_HPP_
#define _CORE_GAME_HPP_

#include <vector>

namespace Core
{

class Frame;
class Event;
class EventManager;
class Layer;

class Game
{
    Frame* m_frame;
    EventManager* m_eventManager;
    std::vector<Layer*> m_layers;
    static Game* m_instance;

private:
    Game(Frame* frame, EventManager* eventManager);
    ~Game();

private:
    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;

public:
    static Game* getInstance(Frame* frame = 0, EventManager* eventManager = 0);

public:
    Event* getEvent();

public:
    void start();
    void pushLayer(Layer* layer);
    void popLayer();

private:
    void mainLoop();
};

} // namespace core

#endif //_CORE_GAME_HPP_

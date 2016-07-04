#ifndef _CORE_GAME_HPP_
#define _CORE_GAME_HPP_

#include "input_manager.hpp"
#include "rectangle.hpp"

#include <vector>

namespace Base
{

class Event;
class InputHandler;

}

namespace Core
{

class Frame;
class Layer;

class Game
{
public:
    typedef std::vector<Layer*> Layers;

private:
    Frame* m_frame = 0;
    Base::InputHandler* m_inputHandler = 0;
    Layers m_layers;
    static Game* m_instance;
    bool m_isRunning = true;
    int m_activeLayerId = 0;

private:
    Game(Frame* frame, Base::InputHandler* inputHandler);
    ~Game();

private:
    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;

public:
    static Game* getInstance(Frame* frame = 0, Base::InputHandler* inputHandler = 0);
    static bool deleteInstance();

public:
    const Frame* frame() const;

    Base::InputHandler* inputHandler();

public:
    void start();
    void pushLayer(Layer* layer);
    void popLayer();
    const Layers& layers() const;
    Rectangle mapRect();
    int activeLayerId() const;

private:
    void mainLoop();
    void quit(Base::Event*);
};

} // namespace core

#endif //_CORE_GAME_HPP_

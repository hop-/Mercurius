#ifndef _CORE_GAME_HPP_
#define _CORE_GAME_HPP_

#include "input_manager.hpp"

#include <vector>

namespace Base
{

class Event;

}

namespace Core
{

class Frame;
class InputHandler;
class Layer;

class Game
{
    Frame* m_frame = 0;
    InputHandler* m_inputHandler = 0;
    std::vector<Layer*> m_layers;
    static Game* m_instance;
    bool m_isRunning = true;

private:
    Game(Frame* frame, InputHandler* inputHandler);
    ~Game();

private:
    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;

public:
    static Game* getInstance(Frame* frame = 0, InputHandler* inputHandler = 0);
    static bool deleteInstance();

public:
    const Frame* frame() const;

    InputHandler* inputHandler()
    {
        return m_inputHandler;
    }

public:
    void start();
    void pushLayer(Layer* layer);
    void popLayer();

private:
    void mainLoop();

    void quit(Base::Event*)
    {
        m_isRunning = false;
    }
};

} // namespace core

#endif //_CORE_GAME_HPP_

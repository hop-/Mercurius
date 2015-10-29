#ifndef _GAME_HPP_
#define _GAME_HPP_

#include <vector>

namespace Core
{

class Frame;
class Layer;

class Game
{
    Core::Frame* m_frame;
    std::vector<Core::Layer*> m_layer;

private:
    void mainLoop();

public:
    virtual ~Game() = default;
    void start();
};

} /// namespace core

#endif //_GAME_HPP_

#include "game.hpp"

#include "layer.hpp"
#include "frame.hpp"

namespace Core
{

void Game::mainLoop()
{
    // TODO
}

void Game::start()
{
    m_frame->init();
    mainLoop();
}

} // namespace core

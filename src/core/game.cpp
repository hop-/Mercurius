#include <game.hpp>

#include <layer.hpp>
#include <frame.hpp>

void Core::Game::mainLoop()
{
    // TODO
}

void Core::Game::start()
{
    m_frame->init();
    mainLoop();
}

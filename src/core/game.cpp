#include "game.hpp"

#include "layer.hpp"
#include "frame.hpp"
#include "event_manager.hpp"
#include "command.hpp"

#include <cassert>

namespace Core
{

Game::Game(Frame* frame, EventManager* eventManager)
    : m_frame(frame)
    , m_eventManager(eventManager)
{}

Game::Game()
    : Game(0, 0)
{}

Game::~Game()
{
    assert(0 != m_frame);
    assert(0 != m_eventManager);
    delete m_frame;
    m_frame = 0;
    delete m_eventManager;
    m_eventManager = 0;
}

void Game::mainLoop()
{
    unsigned previousTicks = m_eventManager->getTicks();
    unsigned realLag = 0;
    const unsigned msToUpdate = m_frame->msPerUpdate();
    // game loop
    while (m_layers.size()) {
        assert(0 != m_eventManager);
        unsigned currentTicks = m_eventManager->getTicks();
        unsigned deltaTicks = currentTicks - previousTicks;
        previousTicks = currentTicks;
        realLag += deltaTicks;
        unsigned lag = realLag;
        // run update for each layer
        for (Layer* layer : m_layers) {
            assert(0 != layer);
            if (layer->isStopped()) {
                continue;
            }
            Command* cmd = m_eventManager->getCommand(layer);
            // assert(0 != cmd);
            if (0 != cmd) {
                cmd->execute();
            }
            lag = realLag;
            while (lag >= msToUpdate) {
                layer->update();
                lag -= msToUpdate;
            }
            layer->draw();
        }
        realLag = lag;
        m_eventManager->pop();
    }
}

void Game::start()
{
    assert(0 != m_frame);
    m_frame->init();
    mainLoop();
}

void Game::pushLayer(Layer* layer)
{
    m_layers.push_back(layer);
}

void Game::popLayer()
{
    return m_layers.pop_back();
}

} // namespace core

#include "game.hpp"

#include "layer.hpp"
#include "frame.hpp"
#include "event_generator.hpp"

namespace Core
{

void Game::mainLoop()
{
    unsigned previousTicks = m_eventGenerator->getTicks();
    unsigned realLag = 0;
    const unsigned msToUpdate = m_frame->msPerUpdate();
    // game loop
    while (m_layers.size()) {
        unsigned currentTicks = m_eventGenerator->getTicks();
        unsigned deltaTicks = currentTicks - previousTicks;
        previousTicks = currentTicks;
        realLag += deltaTicks;
        unsigned lag = realLag;
        // run update for each layer
        for (Layer* layer : m_layers) {
            if (layer->isStopped()) {
                continue;
            }
            // TODO get commands for layer and execute them
            lag = realLag;
            while (lag >= msToUpdate) {
                layer->update();
                lag -= msToUpdate;
            }
            layer->draw(m_frame);
        }
        realLag = lag;
    }
}

void Game::start()
{
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

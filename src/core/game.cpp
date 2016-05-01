#include "game.hpp"

#include "layer.hpp"
#include "frame.hpp"
#include "command.hpp"
#include "events.hpp"

#include <base/event_manager.hpp>

#include <algorithm>
#include <cassert>

namespace Core
{

Game* Game::m_instance = 0;

Game* Game::getInstance(Frame* frame, Base::InputHandler* inputHandler)
{
    if (frame != 0 && inputHandler != 0 && m_instance == 0) {
        m_instance = new Game(frame, inputHandler);
    }
    return m_instance;
}

bool Game::deleteInstance()
{
    if (m_instance == 0) {
        return false;
    }
    delete m_instance;
    m_instance = 0;
    return true;
}

Game::Game(Frame* frame, Base::InputHandler* inputHandler)
    : m_frame(frame)
    , m_inputHandler(inputHandler)
    , m_layers()
{
    assert(0 != m_frame);
    assert(0 != inputHandler);
    QuitEvent::registerCallback(new Base::DelegateCreator<Game>(this, &Game::quit));
}

Game::~Game()
{
    assert(0 != m_frame);
    assert(0 != m_inputHandler);
    delete m_frame;
    m_frame = 0;
    delete m_inputHandler;
    m_inputHandler = 0;
    for (auto l : m_layers) {
        assert(0 != l);
        delete l;
    }
    m_layers.clear();
    assert(m_layers.empty());
    //QuitEvent::removeCallbacks(this);
    // TODO remove callback
}

void Game::mainLoop()
{
    assert(0 != m_inputHandler);
    unsigned previousTicks = m_inputHandler->getTicks();
    unsigned realLag = 0;
    const unsigned msToUpdate = m_frame->msPerUpdate();
    // game loop
    while (m_layers.size() && m_isRunning) {
        assert(0 != m_inputHandler);
        unsigned currentTicks = m_inputHandler->getTicks();
        unsigned deltaTicks = currentTicks - previousTicks;
        previousTicks = currentTicks;
        realLag += deltaTicks;
        m_inputHandler->catchUserInput();
        unsigned lag = realLag;
        // run update for each layer
        while (lag >= msToUpdate) {
            lag -= msToUpdate;
            for (Layer* layer : m_layers) {
                assert(0 != layer);
                if (!layer->isStopped()) {
                    layer->update();
                }
            }
        }
        realLag = lag;
        // clear frame
        m_frame->clear();
        // draw layers on frame
        for (Layer* layer : m_layers) {
            layer->draw();
        }
        // visualize frame
        m_frame->draw();
        Base::EventManager::processAllDeleteEvents();
    }
}

void Game::start()
{
    assert(0 != m_frame);
    m_frame->init();
    std::for_each(m_layers.begin(), m_layers.end(), [](Layer* l) {
        assert(0 != l);
        l->init();
    });
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

const Frame* Game::frame() const
{
    assert(0 != m_frame);
    return m_frame;
}

} // namespace core

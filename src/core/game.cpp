#include "game.hpp"

#include "layer.hpp"
#include "frame.hpp"
#include "event_manager.hpp"
#include "command.hpp"
#include "events.hpp"
#include "input_manager.hpp"

#include <algorithm>
#include <cassert>

namespace Core
{

Game* Game::m_instance = 0;

Game* Game::getInstance(Frame* frame, EventManager* eventManager)
{
    if (frame != 0 && eventManager != 0 && m_instance == 0) {
        m_instance = new Game(frame, eventManager);
        // should be set in another place from configs
        InputManager::reset();
        InputManager::setMapping(InputManager::Key::Left, 80);
        InputManager::setMapping(InputManager::Key::Right, 79);
        InputManager::setMapping(InputManager::Key::Up, 82);
        InputManager::setMapping(InputManager::Key::Down, 81);
        InputManager::setMapping(InputManager::Key::Jump, 44);
        //
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

Game::Game(Frame* frame, EventManager* eventManager)
    : m_frame(frame)
    , m_eventManager(eventManager)
    , m_inputManager()
    , m_layers()
{
    assert(0 != m_frame);
    assert(0 != eventManager);
}

Game::~Game()
{
    assert(0 != m_frame);
    assert(0 != m_eventManager);
    delete m_frame;
    m_frame = 0;
    delete m_eventManager;
    m_eventManager = 0;
    for (auto l : m_layers) {
        assert(0 != l);
        delete l;
    }
    m_layers.clear();
    assert(m_layers.empty());
}

void Game::mainLoop()
{
    unsigned previousTicks = m_eventManager->getTicks();
    unsigned realLag = 0;
    const unsigned msToUpdate = m_frame->msPerUpdate();
    bool finish = false;
    // game loop
    while (m_layers.size() && !finish) {
        assert(0 != m_eventManager);
        unsigned currentTicks = m_eventManager->getTicks();
        unsigned deltaTicks = currentTicks - previousTicks;
        previousTicks = currentTicks;
        realLag += deltaTicks;
        m_eventManager->catchEvent();
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
            // TMP
            Event* e = m_eventManager->getEvent();
            if (e != 0 && Core::QuitEvent::castable(e)) {
                finish = true;
            }
            // END OF TMP
            m_eventManager->pop();
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

Event* Game::getEvent()
{
    assert(0 != m_eventManager);
    return m_eventManager->getEvent();
}

} // namespace core

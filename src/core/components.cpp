#include "components.hpp"
#include "events.hpp"
#include "game.hpp"
#include "gui_object.hpp"
#include <iostream>

namespace Core
{

void ViewPort::target(LogicObject* object)
{
    m_targetObject = object;
}

void ViewPort::aim()
{
    if (0 != m_targetObject) {
        // TODO aim viewPort position to m_targetObject position
    }
}

void ViewPort::update()
{
    aim();
}

void Physics::update()
{
    Position position = parent()->position();
    position.move(m_velocity);
    parent()->setPosition(position);
}

void TextureRenderer::init()
{
    notify();
}

void TextureRenderer::onNotify()
{
    m_position = parent()->position();
    notify();
}

void TextureRenderer::setState(int state)
{
    assert(0 < state);
    assert(m_numberOfStates > state);
    m_state = static_cast<unsigned>(state);
    notify();
}

void Moveable::update()
{
    Game* game = Game::getInstance();
    assert(0 != game);
    Event* event = game->getEvent();
    if (0 == event) {
        return;
    }
    KeyEvent* ke = dynamic_cast<KeyEvent*>(event);
    if (ke != 0) {
        LogicObject* lo = parent();
        assert(0 != lo);
        Physics* ph = lo->component<Physics>();
        assert(0 != ph);
        if (ke->mode() == KeyEvent::Mode::Down) {
            std::cout<<"DOWN"<<std::endl;
            if (ke->key() == 1073741903) { // TODO create Keys codes handler
                ph->setVelocity(Vector(1, 0));
            } else if (ke->key() == 1073741904) { // TODO create Key codes handler
                ph->setVelocity(Vector(1, 180));
            }
        } else {
            std::cout<<"UP"<<std::endl;
            assert(ke->mode() == KeyEvent::Mode::Up);
            ph->setVelocity(Vector(0, 0));
        }
    }
}

} // namespace Core

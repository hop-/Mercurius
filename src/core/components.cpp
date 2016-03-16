#include "components.hpp"
#include "events.hpp"
#include "game.hpp"
#include "frame.hpp"
#include "gui_object.hpp"

namespace Core
{

ViewPort::ViewPort()
    : m_movingArea(UserUnit(15000)
            , UserUnit(15000)
            , Position(UserUnit(-2000), UserUnit(-3000)))    // TODO TMP for testing
{
    setWidth(UserUnit(Game::getInstance()->frame()->width()));
    setHeight(UserUnit(Game::getInstance()->frame()->height()));
}

void ViewPort::target(LogicObject* object)
{
    assert(0 != object);
    object->addObserver(this);
}

void ViewPort::aim()
{
    assert(0 != target());
    Position p(target()->position().x() - middleX()
            , target()->position().y() - middleY());
    if (m_movingArea.isInside(Rectangle(width(), height(), p))) {
        setPosition(p);
    }
}

void ViewPort::onNotify()
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
{/*
    Game* game = Game::getInstance();
    assert(0 != game);
    Event* event = game->getEvent();
    if (0 == event) {
        return;
    }
    KeyEvent* ke = KeyEvent::cast(event);
    if (ke != 0) {
        LogicObject* lo = parent();
        assert(0 != lo);
        Physics* ph = lo->component<Physics>();
        assert(0 != ph);
        if (ke->mode() == KeyEvent::Mode::Down) {
            std::cout << "DOWN - " << ke->key() << std::endl;
            if (ke->key() == 1073741903) { // TODO create Keys codes handler
                ph->setVelocity(Vector(1, 0));
            } else if (ke->key() == 1073741904) { // TODO create Key codes handler
                ph->setVelocity(Vector(1, 180));
            }
        } else {
            std::cout << "UP - " << ke->key() << std::endl;
            assert(ke->mode() == KeyEvent::Mode::Up);
            ph->setVelocity(Vector(0, 0));
        }
    }*/
}

} // namespace Core

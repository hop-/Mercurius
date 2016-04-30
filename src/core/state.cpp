#include "state.hpp"
#include "command.hpp"
#include "events.hpp"
#include <iostream>
namespace Core
{

State::State()
{
    KeyEvent::registerCallback(this, new Base::DelegateCreator<State>(this, &State::onKeyEvent));
    ObjectCollision::registerCallback(this, new Base::DelegateCreator<State>(this, &State::onObjectCollision));
}

State::~State()
{
    KeyEvent::removeCallbacks(this);
    ObjectCollision::removeCallbacks(this);
}

void State::init()
{
    Command* initCommand = onInit();
    if (0 != initCommand) {
        initCommand->execute();
    }
}

} // namespace Core

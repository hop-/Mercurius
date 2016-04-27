#include "state.hpp"
#include "command.hpp"
#include "events.hpp"

namespace Core
{

State::State()
{
    KeyEvent::registerCallback(new Base::DelegateCreator<State>(this, &State::onKeyEvent));
    ObjectCollision::registerCallback(new Base::DelegateCreator<State>(this, &State::onObjectCollision));
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

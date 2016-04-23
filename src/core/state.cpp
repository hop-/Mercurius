#include "state.hpp"
#include "command.hpp"
#include "events.hpp"

namespace Core
{

State::State()
{
    KeyEvent::registerCallback(&State::onKeyEvent, this);
    ObjectCollision::registerCallback(&State::onObjectCollision, this);
}

void State::init()
{
    Command* initCommand = onInit();
    if (0 != initCommand) {
        initCommand->execute();
    }
}

} // namespace Core

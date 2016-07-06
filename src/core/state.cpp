#include "state.hpp"
#include "command.hpp"
#include "events.hpp"

namespace Core
{

State::
State()
{
    registerCallback<KeyEvent>(new Base::DelegateCreator<State>
            (this, &State::onKeyEvent));
    registerCallback<ObjectCollision>(new Base::DelegateCreator<State>
            (this, &State::onObjectCollision));
}

State::
~State()
{}

void State::
init()
{
    Command* initCommand = onInit();
    if (0 != initCommand) {
        initCommand->execute();
    }
}

Command* State::
command()
{
    return 0;
}

Command* State::
onInit()
{
    return 0;
}

} // namespace Core

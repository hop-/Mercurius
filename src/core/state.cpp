#include "state.hpp"
#include "command.hpp"
#include "events.hpp"
#include "logic_object.hpp"

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

void State::
addState(State* newState)
{
    parent<Core::LogicObject>()->addState(newState);
}

void State::
changeState(State* newState)
{
    parent<Core::LogicObject>()->changeState(this, newState);
}

void State::
removeState(State* state)
{
    parent<Core::LogicObject>()->removeState(state);
}

} // namespace Core

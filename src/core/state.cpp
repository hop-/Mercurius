#include "state.hpp"
#include "command.hpp"
#include "events.hpp"
#include <iostream>

namespace Core
{

State::State()
{
    registerCallback<KeyEvent>(new Base::DelegateCreator<State>
            (this, &State::onKeyEvent));
    registerCallback<ObjectCollision>(new Base::DelegateCreator<State>
            (this, &State::onObjectCollision));
}

State::~State()
{}

void State::init()
{
    Command* initCommand = onInit();
    if (0 != initCommand) {
        initCommand->execute();
    }
}

} // namespace Core

#include "state.hpp"
#include "command.hpp"

namespace Core
{

void State::init()
{
    Command* initCommand = onInit();
    if (0 != initCommand) {
        initCommand->execute();
    }
}

} // namespace Core

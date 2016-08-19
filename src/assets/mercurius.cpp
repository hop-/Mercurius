#include "mercurius.hpp"

#include "game.hpp"

#include <core/controller.hpp>

namespace Assets
{

void Mercurius::
startServices()
{
    Game::getInstance();
    MML::MMLManager::getInstance();
    TypeManager::getInstance();
    Core::Controller::getInstance()->initCornerStone();
}

Mercurius::
~Mercurius()
{
    Core::Controller::deleteInstance();
}

} // namespace Assets

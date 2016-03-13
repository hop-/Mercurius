#include "logic.hpp"
#include "logic_object.hpp"
#include "event.hpp"
#include "game.hpp"

namespace Core
{

void Logic::update()
{
    Game* game = Game::getInstance();
    assert(0 != game);
    Event* e = game->getEvent();
    if (0 != e) {
        for (auto* object : children()) {
            assert(0 != object);
            object->process(e);
        }
    }
    for (auto* object : children()) {
        assert(0 != object);
        object->update();
    }
}


Logic::Logic()
{
}

Logic::~Logic()
{
}

} // namespace Core

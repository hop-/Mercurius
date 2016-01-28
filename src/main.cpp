// main.cpp

#include "core/game.hpp"
#include "core/frame.hpp"
#include "core/event_generator.hpp"

#include <mml/mml_manager.hpp>

#include "sdl/frame.hpp"
#include "sdl/event_generator.hpp"

int main(int argc, char** argv)
{
    Core::Frame* frame = new Sdl::Frame;
    Core::EventGenerator* eventGenerator = new Sdl::EventGenerator;
    Core::Game game(frame, eventGenerator);
    game.start();
    MML::MMLManager::getInstance()->loadData("src/mml/test/frame.mml");
    return 0;
}

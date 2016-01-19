// main.cpp

#include "core/game.hpp"
#include "core/frame.hpp"
#include "core/event_generator.hpp"

#include "sdl/frame.hpp"
#include "sdl/event_generator.hpp"

int main(int argc, char** argv)
{
    Core::Frame* frame = new Sdl::Frame;
    Core::EventGenerator* eventGenerator = new Sdl::EventGenerator;
    Core::Game game(frame, eventGenerator);
    game.start();
    return 0;
}

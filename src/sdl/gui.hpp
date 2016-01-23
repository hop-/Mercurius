#ifndef _SDL_GUI_HPP_
#define _SDL_GUI_HPP_

#include <core/gui.hpp>

namespace Sdl
{

class Gui
    : public Core::Gui
{
public:
    Gui(Core::Frame* parent)
        : Core::Gui(parent)
    {}

    void draw();
};

} // namespace Sdl

#endif //_SDL_GUI_HPP_

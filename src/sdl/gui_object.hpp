#ifndef _SDL_GUI_OBJECT_HPP_
#define _SDL_GUI_OBJECT_HPP_

#include <core/gui_object.hpp>

namespace Sdl
{

class GuiObject
    : public Core::GuiObject
{
public:
    void onNotify();
};

} // namespace Sdl

#endif //_SDL_GUI_OBJECT_HPP_
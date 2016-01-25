#ifndef _SDL_GUI_HPP_
#define _SDL_GUI_HPP_

#include <core/gui.hpp>

#include <list>
#include <SDL2/SDL.h>

namespace Sdl
{

class Gui
    : public Core::Gui
{
public:
    Gui(Core::Layer* parent)
        : Core::Gui(parent)
    {}

    void draw();

private:
    virtual void loadGuiObject(GuiObject*);

private:
    Core::Texture* guiObject2Texture(Core::GuiObject* o);
};

} // namespace Sdl

#endif //_SDL_GUI_HPP_

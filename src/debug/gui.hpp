#ifndef _DEBUG_GUI_HPP_
#define _DEBUG_GUI_HPP_

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

namespace Core
{

class GuiObject;

}

namespace Debug
{

class Gui
{
    static bool m_inited;
    static TTF_Font* m_font;
    static SDL_Color m_color;
    static unsigned m_previousTicks;

public:
    static void init();
    static void drawRect(SDL_Renderer* rend, const SDL_Rect* rect);
    static void drawBody(SDL_Renderer* r, const Core::GuiObject* o, int h);
    static void showFPS(SDL_Renderer* rend, unsigned ticks);
};

} // namespace Debug

#endif //_DEBUG_GUI_HPP_

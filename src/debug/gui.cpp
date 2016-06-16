#include "gui.hpp"
#include "log.hpp"

#include <core/gui_object.hpp>
#include <core/logic_object.hpp>
#include <core/components.hpp>
#include <core/rectangle.hpp>
#include <core/units.hpp>

#include <SDL2/SDL_ttf.h>

#include <cassert>
#include <string>
#include <sstream>

namespace Debug
{

bool Gui::m_inited = false;
TTF_Font* Gui::m_font = TTF_OpenFont("./resources/font.mft", 20);
SDL_Color Gui::m_color = {0, 0, 0, 0};
unsigned Gui::m_previousTicks = 0;

#ifdef DM_NO_DEBUG
void Gui::init()
{}

void Gui::drawRect(const SDL_Renderer*, const SDL_Rect*)
{}

void Gui::drawBody(const SDL_Renderer*, const Core::GuiObject*)
{}

void Gui::showFPS(const SDL_Renderer*, unsigned)
{}
#else
void Gui::init()
{
    TTF_Init();
    TTF_CloseFont(m_font);
    m_font = TTF_OpenFont("./resources/font.mft", 20);
    m_inited = true;
}

void Gui::drawRect(SDL_Renderer* rend, const SDL_Rect* rect)
{
    SDL_SetRenderDrawColor(rend, 0xFF, 0x00, 0x00, 0x00);
    SDL_RenderDrawRect(rend, rect);
    SDL_SetRenderDrawColor(rend, 0x00, 0x00, 0x00, 0x00);
}

// TODO
void Gui::drawBody(SDL_Renderer* rend, const Core::GuiObject* o, int hh)
{
    Core::TextureRenderer* t =
        static_cast<Core::TextureRenderer*>(o->subject());
    assert(0 != t);
    assert(0 != t->parent());
    if (0 == t->parent()->component<Core::Collider>()) {
        return;
    }
    Core::Rectangle rect = t->parent()->component<Core::Collider>()->rect().scaled(o->scale());
    SDL_Rect sdlRect = {int(rect.position().x()), int(rect.position().y())
        , int(rect.width()), int(rect.height())
    };
    sdlRect.y = hh - sdlRect.y - sdlRect.h;
    drawRect(rend, &sdlRect);
}

void Gui::showFPS(SDL_Renderer* rend, unsigned ticks)
{
    assert(m_inited);
    assert(m_font);
    unsigned delta = ticks - m_previousTicks;
    std::string fps;
    if (delta) {
        unsigned ufps = 1000 / delta;
        m_previousTicks = ticks;
        std::ostringstream oss;
        oss << ufps;
        fps = oss.str();
    } else {
        fps = "NA";
    }
    fps = "fps: " + fps;
    SDL_Surface* sfc = TTF_RenderText_Solid(m_font, fps.c_str(), m_color);
    assert(0 != sfc);
    SDL_Texture* txtr = SDL_CreateTextureFromSurface(rend, sfc);
    assert(0 != txtr);
    SDL_Rect r = {10, 10, sfc->w, sfc->h};
    SDL_RenderCopy(rend, txtr, 0, &r);
    SDL_DestroyTexture(txtr);
    SDL_FreeSurface(sfc);
}
#endif
} // namespace Debug

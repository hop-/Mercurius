#include "frame.hpp"
#include "texture.hpp"
#include "gui_object.hpp"

#include <cassert>

#ifndef NDEBUG
    #include <SDL2/SDL_ttf.h>
    #include <string>
    #include <sstream>
    #include <iostream>

    #define DRAW_BOARDS(RENDERER, RECT) \
        SDL_SetRenderDrawColor(RENDERER, 0xFF, 0x00, 0x00, 0x00); \
        SDL_RenderDrawRect(RENDERER, RECT); \
        SDL_SetRenderDrawColor(RENDERER, 0x00, 0x00, 0x00, 0x00);

    static unsigned PREVIOUS_TICKS = 0;
    static TTF_Font* FONT = TTF_OpenFont("./resources/font.mft", 12);
    static SDL_Color COLOR = {0, 0, 0, 0};

    #define INIT_TTF() \
        TTF_Init(); \
        TTF_CloseFont(FONT); \
        FONT = TTF_OpenFont("./resources/font.mft", 20);

    #define SHOW_FPS(RENDERER, CURRENT_TICKS) \
        unsigned DELTA_TICKS = CURRENT_TICKS - PREVIOUS_TICKS; \
        unsigned UFPS = 1000 / DELTA_TICKS;\
        PREVIOUS_TICKS = CURRENT_TICKS; \
        std::ostringstream OSS; \
        OSS << UFPS; \
        std::string FPS = "fps = " + OSS.str();\
        assert(0 != FONT); \
        SDL_Surface* SFC = TTF_RenderText_Solid(FONT, FPS.c_str(), COLOR); \
        assert(0 != SFC); \
        SDL_Texture* TXTR = SDL_CreateTextureFromSurface(RENDERER, SFC); \
        assert(0 != TXTR); \
        SDL_Rect R = {10, 10, SFC->w, SFC->h}; \
        SDL_RenderCopy(RENDERER, TXTR, 0, &R); \
        SDL_DestroyTexture(TXTR); \
        SDL_FreeSurface(SFC);
#else
    #define DRAW_BOARDS(RENDERER, RECT)
    #define SHOW_FPS(RENDERER, CURRENT_TICKS)
    #define INIT_TTF()
#endif

namespace Sdl
{

namespace {

SDL_WindowFlags toSDLScreenMode(Core::Frame::ScreenMode m)
{
    switch (m) {
    case Core::Frame::ScreenMode::fullScreen:
        return SDL_WINDOW_FULLSCREEN;
    case Core::Frame::ScreenMode::window:
        return SDL_WINDOW_SHOWN;
    case Core::Frame::ScreenMode::fullScreenFit:
        return SDL_WINDOW_FULLSCREEN_DESKTOP;
    default:
        break;
    }
    assert(!"All core modes should have there corresponding SDL modes");
    return SDL_WINDOW_SHOWN;
}

} // unnamed namespace

Frame::Frame()
    : Core::Frame()
    , m_window(0)
    , m_renderer(0)
{
}

Frame::~Frame()
{
    assert(0 != m_window);
    SDL_DestroyWindow(m_window);
    m_window = 0;
    assert(0 != m_renderer);
    SDL_DestroyRenderer(m_renderer);
    m_renderer = 0;
    SDL_Quit(); // This call may be risky need further investigation
}

void Frame::init()
{
    assert(0 == m_window);
    assert(0 == m_renderer);
    // TODO check SDL_Init(SDL_INIT_VIDEO) == 0 for success
    SDL_Init(SDL_INIT_VIDEO);
    INIT_TTF();
    SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "linear" ); // antialiasing
                                                            // possible:
                                                            // 0 / nearest
                                                            // 1 / linear
                                                            // 2 / best
    m_window = SDL_CreateWindow("Mercurius :P" // TODO title
            , SDL_WINDOWPOS_UNDEFINED
            , SDL_WINDOWPOS_UNDEFINED
            , width()
            , height()
            , toSDLScreenMode(screenMode()));
    assert(0 != m_window);
    correctResolution();
    m_renderer = SDL_CreateRenderer(m_window
            , -1
            , SDL_RENDERER_ACCELERATED);
    assert(0 != m_renderer);
}

void Frame::correctResolution()
{
    int w, h;
    SDL_GetWindowSize(m_window, &w, &h);
    setWidth(w);
    setHeight(h);
}

void Frame::clear()
{
    SDL_RenderClear(m_renderer);
}

void Frame::draw(const Core::GuiObject* object)
{
    assert(0 != object);
    const GuiObject* sdlObject = static_cast<const GuiObject*>(object);
    assert(0 != dynamic_cast<const GuiObject*>(object));
    assert(0 != m_renderer);
    Texture texture = sdlObject->texture();
    assert(0 != texture.texture);
    texture.destinationRect.y = height()
        - texture.destinationRect.y
        - texture.destinationRect.h;
    SDL_RenderCopyEx(m_renderer, texture.texture
            , &(texture.sourceRect)
            , &(texture.destinationRect)
            , 0, 0
            , texture.flip);
    DRAW_BOARDS(m_renderer, &(texture.destinationRect));
}

void Frame::show()
{
    SHOW_FPS(m_renderer, SDL_GetTicks());
    SDL_RenderPresent(m_renderer);
}

} // namespace Sdl

#include "frame.hpp"
#include "texture.hpp"
#include "gui_object.hpp"

#include <cassert>

#ifndef NDEBUG
#define DRAW_BOARDS(RENDERER, RECT) \
    SDL_SetRenderDrawColor(RENDERER, 0xFF, 0x00, 0x00, 0x00); \
    SDL_RenderDrawRect(RENDERER, RECT); \
    SDL_SetRenderDrawColor(RENDERER, 0x00, 0x00, 0x00, 0x00);
#else
#define DRAW_BOARDS(RENDERER, RECT)
#endif

namespace Sdl
{

namespace {

SDL_WindowFlags toSDLScreenMode(Core::Frame::ScreenMode m)
{
    switch (m) {
    case Core::Frame::fullScreen:
        return SDL_WINDOW_FULLSCREEN;
    case Core::Frame::window:
        return SDL_WINDOW_SHOWN;
    case Core::Frame::fullScreenFit:
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
    m_window = SDL_CreateWindow("Mercurius :P" // TODO title
            , SDL_WINDOWPOS_UNDEFINED
            , SDL_WINDOWPOS_UNDEFINED
            , width()
            , height()
            , toSDLScreenMode(screenMode()));
    assert(0 != m_window);
    m_renderer = SDL_CreateRenderer(m_window
            , -1
            , SDL_RENDERER_ACCELERATED);
    assert(0 != m_renderer);
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
    SDL_RenderCopy(m_renderer, texture.texture  // maybe need to be used
            , &(texture.sourceRect)             // SDL_RenderCopyEx(..) to
            , &(texture.destinationRect));      // mirror image left/right
    DRAW_BOARDS(m_renderer, &(texture.destinationRect));
}

void Frame::show()
{
    SDL_RenderPresent(m_renderer);
}

} // namespace Sdl

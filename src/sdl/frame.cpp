#include "frame.hpp"
#include "texture.hpp"
#include "gui_object.hpp"

#include <debug/gui.hpp>

#include <cassert>

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
    Debug::Gui::init();
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
    Debug::Gui::drawRect(m_renderer, &(texture.destinationRect));
}

void Frame::show()
{
    Debug::Gui::showFPS(m_renderer, SDL_GetTicks());
    SDL_RenderPresent(m_renderer);
}

} // namespace Sdl

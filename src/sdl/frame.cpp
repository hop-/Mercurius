#include "frame.hpp"
#include "texture.hpp"
#include "gui_object.hpp"

#include <core/game.hpp>
#include <core/layer.hpp>
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

SDL_Rect* Frame::mapToFrame(SDL_Rect& r, int id)
{
    SDL_Rect* rect = 0;
    switch(layersViewMode()) {
        case LayersViewMode::active:
            rect = mapToActive(r, id);
            break;
        case LayersViewMode::list:
            rect = mapToList(r, id);
            break;
        case LayersViewMode::grid:
//        rect = mapToGrid(r, id);
        break;
    default:
        assert(!"This case shouldn't happen");
    }
    return rect;
}

SDL_Rect* Frame::mapToActive(SDL_Rect& r, int id)
{
    Core::Game* game = Core::Game::getInstance();
    assert(0 != game);
    if (game->activeLayerId() != id) {
        return 0;
    }
    return &r;
}

SDL_Rect* Frame::mapToList(SDL_Rect& r, int id)
{
    SDL_Rect* rect = new SDL_Rect(r);
    const int screenWidth = width();
    const int scaleFactor = screenWidth / (screenWidth / Core::Layer::maxId());
    int pos = (screenWidth / Core::Layer::maxId()) * id;
    rect->x = pos + rect->x / scaleFactor ;
    rect->y /= scaleFactor ;
    rect->w /= scaleFactor ;
    rect->h /= scaleFactor ;
    return rect;
}

/*SDL_Rect* Frame::mapToGrid(SDL_Rect& r, int id)
{
}*/

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
    assert(0 != object->parent());
    Core::Layer* layer = dynamic_cast<Core::Layer*>(object->parent()->parent());
    assert(0 != layer);
    SDL_Rect* dest_rect = mapToFrame(texture.destinationRect, layer->id());
    if (dest_rect == 0) {
        return;
    }
    SDL_RenderCopyEx(m_renderer, texture.texture
            , &(texture.sourceRect)
            , dest_rect
            , 0, 0
            , texture.flip);
    Debug::Gui::drawRect(m_renderer, dest_rect);
}

void Frame::show()
{
    Debug::Gui::showFPS(m_renderer, SDL_GetTicks());
    SDL_RenderPresent(m_renderer);
}

} // namespace Sdl

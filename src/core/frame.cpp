#include "frame.hpp"
#include "gui_object.hpp"

#include <cassert>

namespace Core
{

Frame::Frame()
    : m_msPerUpdate(2)
    , m_width(800)
    , m_height(600)
    , m_screenMode(ScreenMode::fullScreenFit)
    , m_layersViewMode(LayersViewMode::list)
    , m_sortedObjects()
{}

void Frame::draw()
{
    for (auto& objList : m_sortedObjects) {
        for (const auto* object : objList.second) {
            draw(object);
        }
        objList.second.clear();
    }
    m_sortedObjects.clear();
    show();
}

void Frame::prepareToDraw(const GuiObject* object)
{
    assert(0 != object);
    m_sortedObjects[object->priority()].push_back(object);
}

void Frame::setFPS(int fps)
{
    static const int s_max_fps = 1000;
    if (fps > s_max_fps) {
        fps = s_max_fps;
    } else if (fps < 1) {
        fps = 1;
    }
    m_msPerUpdate = s_max_fps / fps;
}

void Frame::setResolution(int width, int height)
{
    m_width = width;
    m_height = height;
}

void Frame::setScreenMode(ScreenMode m)
{
    m_screenMode = m;
}

Frame::ScreenMode Frame::screenMode() const
{
    return m_screenMode;
}

void Frame::setLayersViewMode(LayersViewMode m)
{
    m_layersViewMode = m;
}

Frame::LayersViewMode Frame::layersViewMode() const
{
    return m_layersViewMode;
}

} // namespace Core

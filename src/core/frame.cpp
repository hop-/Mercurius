#include "frame.hpp"

namespace Core
{

Frame::Frame()
    : m_msPerUpdate(2)
    , m_width(800)
    , m_height(600)
    , m_screenMode(fullScreen)
{}

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

} // namespace Core

#include "frame.hpp"

namespace Core
{

Frame::Frame()
    : m_msPerUpdate(2)
{}

void Frame::setResolution(int width, int height)
{
    m_width = width;
    m_height = height;
}

} // namespace Core

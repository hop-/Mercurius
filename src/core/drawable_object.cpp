#include "drawable_object.hpp"

#include <cassert>

namespace Core
{

DrawableObject::
DrawableObject(const std::string& p,
               unsigned w, unsigned h,
               unsigned fw, unsigned fh)
    : m_path(p)
    , m_texture_width(w), m_texture_height(h)
    , m_frame_width(fw), m_frame_height(fh)
{
    assert(!m_path.empty());
    assert(w != 0);
    assert(h != 0);
    assert(fw != 0);
    assert(fh != 0);
}

unsigned DrawableObject::
width() const
{
    return m_texture_width;
}

unsigned DrawableObject::
height() const
{
    return m_texture_height;
}

} // end of namespace Core

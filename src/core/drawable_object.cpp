#include "drawable_object.hpp"

#include <cassert>

namespace Core
{

DrawableObject::
DrawableObject(const std::string& p,
               unsigned w, unsigned h,
               unsigned r, unsigned c)
    : m_path(p)
    , m_width(w), m_height(h)
    , m_rows(r), m_columns(c)
{
    assert(!m_path.empty());
    assert(w != 0);
    assert(h != 0);
    assert(r != 0);
    assert(c != 0);
}

unsigned DrawableObject::
width() const
{
    return m_width;
}

unsigned DrawableObject::
height() const
{
    return m_height;
}

unsigned DrawableObject::
rows() const
{
    return m_rows;
}

unsigned DrawableObject::
columns() const
{
    return m_columns;
}

Rectangle DrawableObject::
rectForState(unsigned s) const
{
    assert(s != 0);
    assert(s < m_rows * m_columns);
    return Rectangle();
}

} // end of namespace Core

#include "drawable_object.hpp"

#include <cassert>

namespace Core
{

DrawableObject::
DrawableObject(const std::string& p,
               unsigned w, unsigned h,
               unsigned fw, unsigned fh)
    : m_path(p)
    , m_textureWidth(w)
    , m_textureHeight(h)
    , m_frameWidth(fw)
    , m_frameHeight(fh)
    , m_currentFrameColumn(0)
    , m_currentFrameRow(0)
    , m_maxColumns(w / fw)
    , m_maxRows(h / fh)
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
    return m_textureWidth;
}

unsigned DrawableObject::
height() const
{
    return m_textureHeight;
}

void DrawableObject::
setFrame(unsigned column, unsigned row)
{
    assert(column < m_maxColumns);
    assert(row < m_maxRows);
    m_currentFrameColumn = column;
    m_currentFrameRow = row;
}

} // end of namespace Core

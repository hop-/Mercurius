#include "frame.hpp"

namespace Core
{

const unsigned Frame::msPerUpdate() const
{
    return m_msPerUpdate;
}

void Frame::setmsPerUpdate(unsigned ms)
{
    m_msPerUpdate = ms;
}

} // namespace Core

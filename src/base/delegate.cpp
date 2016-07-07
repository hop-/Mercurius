#include "delegate.hpp"

namespace Base
{

void Delegate::
activate()
{
    m_isNotActive = false;
}

void Delegate::
deactivate()
{
    m_isNotActive = true;
}

bool Delegate::
isNotActive() const
{
    return m_isNotActive;
}

} // namespace Base

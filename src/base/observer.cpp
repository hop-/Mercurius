#include "observer.hpp"

namespace Base
{

Subject* Observer::
subject() const
{
    return m_subject;
}

void Observer::
setSubject(Subject* subject)
{
    m_subject = subject;
}

} // namespace Base

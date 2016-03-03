#include "subject.hpp"

#include "observer.hpp"

#include <cassert>

namespace Base
{

void Subject::notify()
{
    for (Observer* observer : m_observersToNotify) {
        assert(0 != observer);
        observer->onNotify();
    }
}

void Subject::addObserver(Observer* observer)
{
    assert(0 != observer);
    m_observersToNotify.push_back(observer);
    observer->setSubject(this);
}

void Subject::removeObserver(Observer* observer)
{
    assert(0 != observer);
    if (observer->subject() != this) {
        return;
    }
    m_observersToNotify.remove(observer);
    observer->setSubject(0);
}

} // namespace Base

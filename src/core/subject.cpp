#include "subject.hpp"

#include "observer.hpp"

namespace Core
{

void Subject::notify()
{
    for (Observer* observer : m_observersToNotify) {
        observer->onNotify();
    }
}

void Subject::addObserver(Observer* observer)
{
    m_observersToNotify.push_back(observer);
}

void Subject::removeObserver(Observer* observer)
{
    m_observersToNotify.remove(observer);
}

} /// namespace Core

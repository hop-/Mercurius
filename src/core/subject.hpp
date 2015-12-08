#ifndef _CORE_SUBJECT_HPP_
#define _CORE_SUBJECT_HPP_

#include <list>

namespace Core
{

class Observer;

class Subject
{
    std::list<Observer*> m_observersToNotify;

protected:
    Subject() = default;

public:
    void notify();
    void addObserver(Observer* observer);
    void removeObserver(Observer* observer);
};

} // namespace Core

#endif //_CORE_SUBJECT_HPP_

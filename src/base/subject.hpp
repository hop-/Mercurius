#ifndef _BASE_SUBJECT_HPP_
#define _BASE_SUBJECT_HPP_

#include <list>

namespace Base
{

class Observer;

class Subject
{
    std::list<Observer*> m_observersToNotify;

protected:
    Subject();
    virtual ~Subject() = default;

public:
    void notify();
    void addObserver(Observer* observer);
    void removeObserver(Observer* observer);
};

} // namespace Base

#endif //_BASE_SUBJECT_HPP_

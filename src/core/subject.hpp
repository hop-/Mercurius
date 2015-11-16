#ifndef _SUBJECT_HPP_
#define _SUBJECT_HPP_

#include <list>

namespace Core
{

class Observer;

class Subject
{
    std::list<Observer*> m_observersToNotify;

public:
    void notify();
    void addObserver(Observer* observer);
    void removeObserver(Observer* observer);
};

} /// namespace Core

#endif //_SUBJECT_HPP_

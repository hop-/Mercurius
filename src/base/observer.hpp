#ifndef _BASE_OBSERVER_HPP_
#define _BASE_OBSERVER_HPP_

namespace Base
{

class Subject;

class Observer
{
    Subject* m_subject = 0;
public:
    virtual ~Observer() = default;
    virtual void onNotify() = 0;

    inline Subject* subject() const
    {
        return m_subject;
    }

    inline void setSubject(Subject* subject)
    {
        m_subject = subject;
    }
};

} // namespace Base

#endif //_BASE_OBSERVER_HPP_

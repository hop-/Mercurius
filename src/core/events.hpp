#ifndef _CORE_EVENTS_HPP_
#define _CORE_EVENTS_HPP_

#include "event.hpp"

namespace Core
{

class KeyEvent
    : public EventCreator<KeyEvent>
{
public:
    enum Mode {Up, Down}; 

private:
    int m_keyCode;
    Mode m_mode;

public:
    KeyEvent(int keyCode, Mode mode)
    : m_keyCode(keyCode)
    , m_mode(mode)
    {}

    bool less(TypedBase* obj);

    inline int key() const
    {
        return m_keyCode;
    }

    inline Mode mode() const
    {
        return m_mode;
    }
};

class QuitEvent
    : public EventCreator<QuitEvent>
{
    bool less(TypedBase* obj);
};

} // namespace Core

#endif //_CORE_EVENTS_HPP_

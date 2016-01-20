#include "events.hpp"

namespace Core
{


bool KeyEvent::less(TypedBase* obj)
{
    KeyEvent* keyEvent = static_cast<KeyEvent*>(obj);
    return (m_keyCode < keyEvent->key() 
            || (m_keyCode == keyEvent->key() && m_mode < keyEvent->mode()));
}

bool QuitEvent::less(TypedBase* obj)
{
    return false;
}


} // namespace Sdl

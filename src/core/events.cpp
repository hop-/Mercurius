#include "events.hpp"

namespace Core
{


bool KeyEvent::less(Base::TypedBase* obj)
{
    KeyEvent* keyEvent = static_cast<KeyEvent*>(obj);
    return (m_keyCode < keyEvent->key() 
            || (m_keyCode == keyEvent->key() && m_mode < keyEvent->mode()));
}

bool MouseClickEvent::less(Base::TypedBase* obj)
{
    MouseClickEvent* mouseEvent = static_cast<MouseClickEvent*>(obj);
    return (m_button < mouseEvent->button()
            && m_mode < mouseEvent->mode()
            && (m_y < mouseEvent->y()
                || (m_y == mouseEvent->y() && m_x < mouseEvent->x())));
}

bool QuitEvent::less(Base::TypedBase* obj)
{
    return false;
}


} // namespace Sdl

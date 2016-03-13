#include "input_manager.hpp"

namespace Core
{

InputManager::InputManager()
{
    m_keyMap[80] = Key::Left;
    m_keyMap[79] = Key::Right;
    m_keyMap[82] = Key::Up;
    m_keyMap[81] = Key::Down;
    m_keyMap[44] = Key::Jump;
}

} // namespace Core

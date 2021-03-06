#include "input_manager.hpp"

#include <cassert>
#include <algorithm>
#include <cassert>

namespace Core
{

InputManager::Key InputManager::m_keyMap[256];

InputManager::Key InputManager::
operator [](int id) const
{
    assert(id >= 0);
    assert(id < 256);
    return m_keyMap[id];
}

InputManager::Key InputManager::
key(int id)
{
    assert(id >= 0);
    assert(id < 256);
    return m_keyMap[id];
}

void InputManager::
setMapping(InputManager::Key key, int id)
{
    assert(Key::None != key);
    assert(id >= 0);
    assert(id < 256);
    m_keyMap[id] = key;
}

void InputManager::
setMappings(const InputManager::Key keys[])
{
    for (int i = 0 ; i < 256; ++i) {
        m_keyMap[i] = keys[i];
    }
}

void InputManager::
reset()
{
    std::fill_n(m_keyMap, 256, Key::None);
}

} // namespace Core

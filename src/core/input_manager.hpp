#ifndef _CORE_INPUT_MANAGER_HPP_
#define _CORE_INPUT_MANAGER_HPP_

#include <map>
#include <cassert>

namespace Core
{

class InputManager
{
public:
    enum class Key
    {
        Left = 0,
        Right,
        Up,
        Down,
        Jump,
        None,
    };

private:
    std::map<int, Key> m_keyMap;

public:

    InputManager();

    Key operator [](int id) const
    {
        try {
            return m_keyMap.at(id);
        } catch (const std::out_of_range& e) {
            return Key::None;
        }
    }

    void set(Key key, int muppingValue)
    {
        assert(Key::None != key);
        m_keyMap[muppingValue] = key;
    }
};

} // namespace Core

#endif //_CORE_INPUT_MANAGER_HPP_

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
    static Key m_keyMap[256];

public:
    Key operator [](int id) const;
    static Key key(int id);
    static void setMapping(Key key, int muppingValue);
    static void setMappings(Key*);
    static void reset();
};

} // namespace Core

#endif //_CORE_INPUT_MANAGER_HPP_

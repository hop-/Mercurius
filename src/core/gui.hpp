#ifndef _CORE_GUI_HPP_
#define _CORE_GUI_HPP_

#include <cassert>

namespace Core
{

class Frame;

class Gui
{
    Frame* m_parent;

public:
    Gui(Frame* parent)
        : m_parent(parent)
    {
        assert(0 != parent);
    }
    virtual ~Gui() = default;

public:
    virtual void draw() = 0;

protected:
    inline Frame* parent() const
    {
        return m_parent;
    }

    inline void setParent(Frame* parent)
    {
        assert(0 != parent);
        m_parent = parent;
    }
};

} // namespace Core

#endif //_CORE_GUI_HPP_

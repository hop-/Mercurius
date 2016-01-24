#ifndef _CORE_GUI_HPP_
#define _CORE_GUI_HPP_

#include <cassert>

namespace Core
{

class Frame;
class Layer;

class Gui
{
    Layer* m_parent;

public:
    Gui(Layer* parent)
        : m_parent(parent)
    {
        assert(0 != parent);
    }
    virtual ~Gui() = default;

public:
    virtual void draw(Frame*) = 0;

protected:
    inline Layer* parent() const
    {
        return m_parent;
    }

    inline void setParent(Layer* parent)
    {
        assert(0 != parent);
        m_parent = parent;
    }
};

} // namespace Core

#endif //_CORE_GUI_HPP_

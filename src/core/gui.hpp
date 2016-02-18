#ifndef _CORE_GUI_HPP_
#define _CORE_GUI_HPP_

#include <vector>
#include <cassert>

namespace Core
{

class Frame;
class Layer;
class GuiObject;
class Rectangle;

class Gui
{
public:
    typedef std::vector<GuiObject*> GuiObjects;
    
private:
    Layer* m_parent;
    GuiObjects m_objects;
    Rectangle* m_viewPort;
    Frame* m_frame;

public:
    Gui()
        : m_parent(0)
    {
    }
    virtual ~Gui() = default; // TODO implement and delete all children

public:
    void addGuiObject(GuiObject* o);
    void removeGuiObject(GuiObject* o);

    inline Frame* frame() const
    {
        return m_frame;
    }

    inline void setFrame(Frame* frame)
    {
        assert(0 != frame);
        m_frame = frame;
    }

    inline void setViewPort(Rectangle* viewPort)
    {
        assert(0 != viewPort);
        m_viewPort = viewPort;
    }

public:
    void draw();

public:
    inline Layer* parent() const
    {
        return m_parent;
    }

    inline const GuiObjects& objects() const
    {
        return m_objects;
    }

    inline void setParent(Layer* parent)
    {
        assert(0 != parent);
        m_parent = parent;
    }
};

} // namespace Core

#endif //_CORE_GUI_HPP_

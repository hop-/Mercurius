#ifndef _CORE_GUI_HPP_
#define _CORE_GUI_HPP_

#include "gui_object.hpp"

#include <base/container_object.hpp>

#include <vector>

namespace Core
{

class Frame;
class Layer;
class Rectangle;

class Gui
    : public Base::ContainerObject<GuiObject>
{
private:
    Rectangle* m_viewPort;
    Frame* m_frame;

private:
    virtual void initObject()
    {}

public:
    Gui()
        : m_frame(0)
    {
    }
    virtual ~Gui();

public:
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
};

} // namespace Core

#endif //_CORE_GUI_HPP_

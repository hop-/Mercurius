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
    const Rectangle* m_viewPort;
    Frame* m_frame;

private:
    virtual void initObject()
    {}

public:
    Gui()
        : Base::ContainerObject<GuiObject>()
        , m_viewPort(0)
        , m_frame(0)
    {
    }
    virtual ~Gui();

private:
    Gui(const Gui&) = delete;
    Gui& operator=(const Gui&) = delete;

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

    inline void setViewPort(const Rectangle* viewPort)
    {
        assert(0 != viewPort);
        m_viewPort = viewPort;
    }

    inline const Rectangle* viewPort() const
    {
        return m_viewPort;
    }

public:
    float scale() const;
    void draw();
};

} // namespace Core

#endif //_CORE_GUI_HPP_

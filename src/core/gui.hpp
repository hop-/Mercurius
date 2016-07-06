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
    Gui();
    virtual ~Gui();

private:
    Gui(const Gui&) = delete;
    Gui& operator=(const Gui&) = delete;

public:
    Frame* frame() const;
    void setFrame(Frame* frame);
    void setViewPort(const Rectangle* viewPort);
    const Rectangle* viewPort() const;

public:
    float scale() const;
    void draw();
};

} // namespace Core

#endif //_CORE_GUI_HPP_

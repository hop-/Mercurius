#ifndef _CORE_GUI_OBJECT_HPP_
#define _CORE_GUI_OBJECT_HPP_

#include "rectangle.hpp"
#include "units.hpp"
#include "position.hpp"

#include <base/object.hpp>
#include <base/observer.hpp>

#include <string>

namespace Core
{

class Gui;
class LogicObject;
class TextureRenderer;

class GuiObject
    : public Base::Object
    , public Base::Observer
{
    std::string m_textureLocation;
    float m_scaleFactor = 1;
    int m_priority = 0;
    int m_state = 0;
    Rectangle m_rect;
    HorizontalDirection m_direction = HorizontalDirection::Right;

protected:
    GuiObject();

public:
    virtual ~GuiObject() = default;

public:
    void onNotify();
    void setDimensions(UserUnit w, UserUnit h, float scale);
    Rectangle rect() const;
    float scale() const;
    const Rectangle& realRect() const;
    UserUnit width() const;
    UserUnit height() const;
    int priority() const;
    float scaleFactor() const;
    void setPriority(int priority);

protected:
    const TextureRenderer* textureRenderer() const;
    const Gui* guiManager() const;
    HorizontalDirection direction() const;
    UserUnit x() const;
    UserUnit y() const;
    int state() const;
    const std::string& textureLocation() const;
    void setTextureLocation(const std::string& textureLocation);
};

} // namespace Core

#endif //_CORE_GUI_OBJECT_HPP_

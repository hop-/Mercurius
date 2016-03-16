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
    Rectangle m_realRect;

protected:
    GuiObject();

public:
    virtual ~GuiObject() = default;

public:
    void onNotify();

    void setDimensions(UserUnit w, UserUnit h, float scale);

    inline UserUnit width() const
    {
        return m_realRect.width();
    }

    inline UserUnit height() const
    {
        return m_realRect.height();
    }

    inline int priority() const
    {
        return m_priority;
    }

    inline float scaleFactor() const
    {
        return m_scaleFactor;
    }

    inline void setPriority(int priority)
    {
        m_priority = priority;
    }
    void updatePosInViewPort();

protected:
    inline const TextureRenderer* textureRenderer() const;
    inline const Gui* guiManager() const;

    inline UserUnit x() const
    {
        return m_rect.position().x();
    }

    inline UserUnit y() const
    {
        return m_rect.position().y();
    }

    inline int state() const
    {
        return m_state;
    }

    inline const std::string textureLocation() const
    {
        return m_textureLocation;
    }

    inline void setTextureLocation(const std::string& textureLocation)
    {
        m_textureLocation = textureLocation;
    }
};

} // namespace Core

#endif //_CORE_GUI_OBJECT_HPP_

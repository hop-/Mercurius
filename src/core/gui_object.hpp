#ifndef _CORE_GUI_OBJECT_HPP_
#define _CORE_GUI_OBJECT_HPP_

#include "rectangle.hpp"

#include <base/object.hpp>
#include <base/observer.hpp>

#include <string>
#include <cassert>

namespace Core
{

class Gui;
class LogicObject;

class GuiObject
    : public Base::Object
    , public Base::Observer
{
    std::string m_textureLocation;
    Rectangle m_srcRect;    // not the best way
    Rectangle m_destRect;   // not the best way

protected:
    GuiObject();

public:
    virtual ~GuiObject() = default;

public:
    void setDimensions(Rectangle rect, float scale);

    inline Rectangle srcRect() const
    {
        return m_srcRect;
    }

    inline Rectangle destRect() const
    {
        return m_destRect;
    }

protected:
    inline void setSrcRect(Rectangle rect)
    {
        m_srcRect = rect;
    }

    inline void setDestRect(Rectangle rect)
    {
        m_destRect = rect;
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

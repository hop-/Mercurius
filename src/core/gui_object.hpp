#ifndef _CORE_GUI_OBJECT_HPP_
#define _CORE_GUI_OBJECT_HPP_

#include "rectangle.hpp"
#include <base/observer.hpp>

#include <string>
#include <cassert>

namespace Core
{

class Gui;
class LogicObject;

class GuiObject
    : public Base::Observer
{
    Gui* m_parent;
    LogicObject* m_logicObject;
    std::string m_textureLocation;
    Rectangle m_srcRect;    // not the best way
    Rectangle m_destRect;   // not the best way

protected:
    GuiObject(Gui* parnet);

public:
    virtual ~GuiObject() = default;

public:
    virtual void init() = 0;

    inline Rectangle srcRect() const
    {
        return m_srcRect;
    }

    inline Rectangle destRect() const
    {
        return m_destRect;
    }

    inline void setSrcRect(Rectangle rect)
    {
        m_srcRect = rect;
    }

    inline void setDestRect(Rectangle rect)
    {
        m_destRect = rect;
    }

    inline LogicObject* logicObject() const
    {
        return m_logicObject;
    }

    inline void setLogicObject(LogicObject* logicObject)
    {
        m_logicObject = logicObject;
    }

protected:
    inline const std::string textureLocation() const
    {
        return m_textureLocation;
    }

    inline void setTextureLocation(const std::string& textureLocation)
    {
        m_textureLocation = textureLocation;
    }

    inline const Gui* parent() const
    {
        return m_parent;
    }

    void setParent(Gui* parent);
};

} // namespace Core

#endif //_CORE_GUI_OBJECT_HPP_

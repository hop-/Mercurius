#ifndef _CORE_GUI_OBJECT_HPP_
#define _CORE_GUI_OBJECT_HPP_

#include "rectangle.hpp"
#include "units.hpp"
#include "position.hpp"

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
    int m_width = 0;
    int m_height = 0;
    float m_scaleFactor = 1;
    int m_priority = 0;
    int m_x = 0;
    int m_y = 0;
    int m_state = 0;
//    Rectangle m_srcRect;    // not the best way
//    Rectangle m_destRect;   // not the best way

protected:
    GuiObject();

public:
    virtual ~GuiObject() = default;

public:
    void onNotify();

    void setDimensions(UserUnit w, UserUnit h, float scale);

    inline int width() const
    {
        return m_width;
    }

    inline int height() const
    {
        return m_height;
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

protected:
    inline int x() const
    {
        return m_x;
    }

    inline int y() const
    {
        return m_y;
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

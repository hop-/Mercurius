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
    Position m_position;
//    Rectangle m_srcRect;    // not the best way
//    Rectangle m_destRect;   // not the best way

protected:
    GuiObject();

public:
    virtual ~GuiObject() = default;

public:
    void setDimensions(int w, int h, float scale);

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

#ifndef _CORE_GUI_OBJECT_HPP_
#define _CORE_GUI_OBJECT_HPP_

#include "observer.hpp"
#include "mml/mml.hpp"

#include <string>
#include <cassert>

namespace Core
{

class Gui;
class Texture;

class GuiObject
    : public Observer
{
    MML m_mml;
    Gui* m_parent;
    std::string m_textureLocation;
    Texture* m_texture;

protected:
    GuiObject(Gui* parnet, const std::string& config);

public:
    virtual ~GuiObject() = default;

public:
    inline Texture* texture() const
    {
        return m_texture;
    }

protected:
    inline void setTexture(Texture* texture)
    {
        m_texture = texture;
    }

    inline const std::string textureLocation() const
    {
        return m_textureLocation;
    }

    inline void setTectureLocation(std::string textureLocation)
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

#ifndef _CORE_GUI_OBJECT_HPP_
#define _CORE_GUI_OBJECT_HPP_

#include "observer.hpp"
#include "mml/mml.hpp"

#include <string>
#include <cassert>

namespace Core
{

class Gui;

class GuiObject
    : public Observer
{
    MML m_mml;
    Gui* m_parent;

protected:
    GuiObject(Gui* parnet, const std::string& config);

public:
    virtual ~GuiObject() = default;

protected:
    inline Gui* parent() const
    {
        return m_parent;
    }

    inline void setParent(Gui* parent)
    {
        assert(0 != parent);
        m_parent = parent;
    }
};

} // namespace Core

#endif //_CORE_GUI_OBJECT_HPP_

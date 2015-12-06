#ifndef _GUI_OBJECT_HPP_
#define _GUI_OBJECT_HPP_

#include "observer.hpp"
#include "mml.hpp"

#include <string>

namespace Core
{

class GuiObject :
    public Observer
{
    MML m_mml;

protected:
    GuiObject(std::string config);

public:
    virtual ~GuiObject() = default;
};

} // namespace Core

#endif //_GUI_OBJECT_HPP_

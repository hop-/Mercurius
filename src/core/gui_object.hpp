#ifndef _CORE_GUI_OBJECT_HPP_
#define _CORE_GUI_OBJECT_HPP_

#include "observer.hpp"
#include "mml/mml.hpp"

#include <string>

namespace Core
{

class GuiObject
    : public Observer
{
    MML m_mml;

protected:
    GuiObject(const std::string& config);

public:
    virtual ~GuiObject() = default;
};

} // namespace Core

#endif //_CORE_GUI_OBJECT_HPP_

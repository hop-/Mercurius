#ifndef _CORE_GUI_HPP_
#define _CORE_GUI_HPP_

namespace Core
{

class Gui
{
public:
    virtual ~Gui() = default;
    virtual void draw() = 0;
};

} // namespace Core

#endif //_CORE_GUI_HPP_

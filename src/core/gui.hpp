#ifndef _GUI_HPP_
#define _GUI_HPP_

namespace Core
{

class Gui
{
public:
    virtual ~Gui() = default;
    virtual void draw() = 0;
};

} // namespace Core

#endif //_GUI_HPP_

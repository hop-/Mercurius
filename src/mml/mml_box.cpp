#include "mml_box.hpp"
#include "mml_attribute.hpp"

namespace MML
{

MMLObject* MMLBox::BoxFactory::
create(const std::string& n)
{
    return new MMLBox(n);
}

MMLBox::
MMLBox(const std::string& n)
    : MMLObject(n)
{
    setType("box");
    addAttribute(new MMLAttribute("width", 0));
    addAttribute(new MMLAttribute("height", 0));
    addAttribute(new MMLAttribute("weight", 0));
    addAttribute(new MMLAttribute("position_x", 0.0));
    addAttribute(new MMLAttribute("position_y", 0.0));
    addAttribute(new MMLAttribute("texture", ""));
}

int MMLBox::
getWidth() const
{
    const MMLAttribute* width = getAttribute("width");
    assert(0 != width);
    return width->getValue<int>();
}

int MMLBox::
getHeight() const
{
    const MMLAttribute* height = getAttribute("height");
    assert(0 != height);
    return height->getValue<int>();
}

} // MML

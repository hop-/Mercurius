#include "dude.hpp"

namespace MML
{

MMLObject* Dude::Factory::create(const std::string& n)
{
    return new Dude(n);
}

Dude::Dude(const std::string& n)
    : MMLObject(n)
{
    setType("dude");
    addAttribute(new MMLAttribute("width", 0));
    addAttribute(new MMLAttribute("height", 0));
    addAttribute(new MMLAttribute("weight", 0));
    addAttribute(new MMLAttribute("position_x", 0));
    addAttribute(new MMLAttribute("position_y", 0));
    addAttribute(new MMLAttribute("texture", std::string("")));
}

} // namespace MML

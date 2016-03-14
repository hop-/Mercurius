#include "drawable_object.hpp"

namespace MML {

DrawableObject::
DrawableObject(const std::string& name)
    : MMLObject(name)
{
    addAttribute(new MMLAttribute("width", 0));
    addAttribute(new MMLAttribute("height", 0));
    addAttribute(new MMLAttribute("weight", 0));
    addAttribute(new MMLAttribute("scale", double(1)));
    addAttribute(new MMLAttribute("priority", 0));
    addAttribute(new MMLAttribute("position", MMLAttribute::IntPair(0, 0)));
    addAttribute(new MMLAttribute("texture", std::string("")));
}

} // namespace MML

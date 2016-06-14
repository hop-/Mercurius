#include "drawable_object.hpp"

namespace MML {

DrawableObject::
DrawableObject(const std::string& name)
    : MMLObject(name)
{
    addAttribute(new MMLAttribute("width", double(0)));
    addAttribute(new MMLAttribute("height", double(0)));
    addAttribute(new MMLAttribute("weight", double(0)));
    addAttribute(new MMLAttribute("scale", double(1)));
    addAttribute(new MMLAttribute("priority", 0));
    addAttribute(new MMLAttribute("aimed", bool(false)));
    addAttribute(new MMLAttribute("position", MMLAttribute::IntPair(0, 0)));
    addAttribute(new MMLAttribute("body", MMLAttribute::Pair(0.0f, 0.0f)));
    addAttribute(new
            MMLAttribute("offset", MMLAttribute::Pair(0.0f, 0.0f)));
    addAttribute(new MMLAttribute("texture", std::string("")));
}

} // namespace MML

#include "animation.hpp"

namespace MML {


MMLObject* Animation::Factory::
create(const std::string& n)
{
    return new Animation(n);
}

Animation::
Animation(const std::string& name)
    : MMLObject(name)
{
    setType("animation");
    addAttribute(new MMLAttribute("size", MMLAttribute::IntPair(0, 0)));
    addAttribute(new MMLAttribute("frameSize", MMLAttribute::IntPair(0, 0)));
    addAttribute(new MMLAttribute("path", std::string()));
}

} // end of namespace MML

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
    addAttribute(new MMLAttribute("position", MMLAttribute::IntPair(0,0)));
    addAttribute(new MMLAttribute("frameCount", int(0)));
    addAttribute(new MMLAttribute("loop", bool(false)));
    addAttribute(new MMLAttribute("fps", int(60)));
}

} // end of namespace MML

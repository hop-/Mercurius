#include "config.hpp"

namespace MML {

MMLObject* Config::Factory::
create(const std::string& n)
{
    return new Config(n);
}

Config::
Config(const std::string& name)
    : MMLObject(name)
{
    setType("config");
    addAttribute(new MMLAttribute("resolution", MMLAttribute::IntPair(800, 600)));
    addAttribute(new MMLAttribute("screenMode", MMLAttribute::ScreenMode::fullScreenFit));
    addAttribute(new MMLAttribute("default", bool(false)));
    addAttribute(new MMLAttribute("left", 80));
    addAttribute(new MMLAttribute("right", 79));
    addAttribute(new MMLAttribute("up", 82));
    addAttribute(new MMLAttribute("down", 81));
    addAttribute(new MMLAttribute("jump", 44));
}

} // end of namespace MML

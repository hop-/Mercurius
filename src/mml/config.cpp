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
}

} // end of namespace MML

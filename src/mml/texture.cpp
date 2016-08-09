#include "texture.hpp"

namespace MML {


MMLObject* Texture::Factory::
create(const std::string& n)
{
    return new Texture(n);
}

Texture::
Texture(const std::string& name)
    : MMLObject(name)
{
    setType("texture");
    addAttribute(new MMLAttribute("size", MMLAttribute::IntPair(0, 0)));
    addAttribute(new MMLAttribute("frameSize", MMLAttribute::IntPair(0, 0)));
    addAttribute(new MMLAttribute("path", std::string()));
}

} // end of namespace MML

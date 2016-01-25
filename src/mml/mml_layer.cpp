#include "mml_layer.hpp"
#include "mml_attribute.hpp"

namespace MML
{

MMLLayer::
MMLLayer(const std::string& n)
    : MMLObject(n)
{
    addAttribute(new MMLAttribute("visible", false));
}

} // MML

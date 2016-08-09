#include "mml_layer.hpp"
#include "mml_attribute.hpp"
#include "mml_manager.hpp"
#include "mml_registery.hpp"

namespace MML
{

MMLObject* MMLLayer::LayerFactory::
create(const std::string& n)
{
    return new MMLLayer(n);
}

MMLLayer::
MMLLayer(const std::string& n)
    : MMLObject(n)
{
    setType("layer");
    addAttribute(new MMLAttribute("visible", false));
    addAttribute(new MMLAttribute("stopped", false));
}

MMLLayer::
~MMLLayer()
{
}

} // MML

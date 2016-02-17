#include "mml_layer.hpp"
#include "mml_attribute.hpp"
#include "mml_manager.hpp"

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
    addAttribute(new MMLAttribute("level", 0));
    MMLManager* m = MMLManager::getInstance();
    assert(0 != m);
    MMLRegistery* r = m->getLayerRegistery();
    assert(0 != r);
    r->addObject(this);
}

MMLLayer::
~MMLLayer()
{
    MMLManager* m = MMLManager::getInstance();
    assert(0 != m);
    MMLRegistery* r = m->getLayerRegistery();
    assert(0 != r);
    r->removeObject(this);
}

} // MML

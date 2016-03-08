#include "factories.hpp"
#include "box.hpp"
#include "dude.hpp"
#include "gui_object.hpp"
#include "type_manager.hpp"

#include <mml/mml_box.hpp>
#include <mml/mml_layer.hpp>
#include <mml/dude.hpp>

namespace Sdl
{

Base::Object* LayerFactory::
create(const MML::MMLObject* mml, Base::Object*) const
{
    assert(0 != mml);
    const MML::MMLLayer* mml_layer = dynamic_cast<const MML::MMLLayer*>(mml);
    assert(0 != mml_layer);
    Core::Gui* gui = new Core::Gui();
    Core::Logic* logic = new Core::Logic();
    Core::Layer* layer = new Core::Layer(gui, logic, Core::Controls(), false, !mml_layer->isVisible());
    // TODO get attributes from mml_layer and set on layer
    TypeManager* tm = TypeManager::getInstance();
    assert(0 != tm);
    typedef MML::MMLObject::MMLChildren Children;
    const Children& children = mml_layer->getChildren();
    for(auto obj : children) {
            assert(0 != obj);
            const Core::ObjectsFactory* f = tm->getFactory(obj->getType());
            assert(0 != f);
            f->create(obj, layer);
    }
    return layer;
}

Base::Object* BoxFactory::
create(const MML::MMLObject* mml, Base::Object* p) const
{
    assert(0 != mml);
    assert(0 != p);
    const MML::MMLBox* box = dynamic_cast<const MML::MMLBox*>(mml);
    assert(0 != box);
    Core::Layer* l = dynamic_cast<Core::Layer*>(p);
    assert(0 != l);
    return new Box(box, l);
}

Base::Object* DudeFactory::create(const MML::MMLObject* mml
        , Base::Object* p) const
{
    assert(0 != mml);
    assert(0 != p);
    const MML::Dude* dude = dynamic_cast<const MML::Dude*>(mml);
    assert(0 != dude);
    Core::Layer* layer = dynamic_cast<Core::Layer*>(p);
    assert(0 != layer);
    return new Dude(dude, layer);
}

} // namespace Sdl

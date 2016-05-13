#include "factories.hpp"
#include "background.hpp"
#include "box.hpp"
#include "dude.hpp"
#include "door.hpp"
#include "ground.hpp"
#include "ladder.hpp"
#include "type_manager.hpp"

#include <mml/mml_box.hpp>
#include <mml/mml_layer.hpp>
#include <mml/background.hpp>
#include <mml/dude.hpp>
#include <mml/door.hpp>
#include <mml/ground.hpp>
#include <mml/ladder.hpp>

namespace Assets
{

Base::Object* LayerFactory::
create(const MML::MMLObject* mml, Base::Object*) const
{
    assert(0 != mml);
    const MML::MMLLayer* mml_layer = dynamic_cast<const MML::MMLLayer*>(mml);
    assert(0 != mml_layer);
    Core::Gui* gui = new Core::Gui();
    Core::Logic* logic = new Core::Logic();
    Core::Layer* layer = new Core::Layer(gui, logic, mml_layer->isStopped(), !mml_layer->isVisible());
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

Base::Object* DoorFactory::create(const MML::MMLObject* mml
        , Base::Object* p) const
{
    assert(0 != mml);
    assert(0 != p);
    const MML::Door* door = dynamic_cast<const MML::Door*>(mml);
    assert(0 != door);
    Core::Layer* layer = dynamic_cast<Core::Layer*>(p);
    assert(0 != layer);
    return new Door(door, layer);
}

Base::Object* GroundFactory::create(const MML::MMLObject* mml
        , Base::Object* p) const
{
    assert(0 != mml);
    assert(0 != p);
    const MML::Ground* ground = dynamic_cast<const MML::Ground*>(mml);
    assert(0 != ground);
    Core::Layer* layer = dynamic_cast<Core::Layer*>(p);
    assert(0 != layer);
    return new Ground(ground, layer);
}

Base::Object* BackgroundFactory::create(const MML::MMLObject* mml,
        Base::Object* p) const
{
    assert(0 != mml);
    assert(0 != p);
    const MML::Background* bg = dynamic_cast<const MML::Background*>(mml);
    assert(0 != bg);
    Core::Layer* layer = dynamic_cast<Core::Layer*>(p);
    assert(0 != layer);
    return new Background(bg, layer);
}

Base::Object* LadderFactory::create(const MML::MMLObject* mml
        , Base::Object* p) const
{
    assert(0 != mml);
    assert(0 != p);
    const MML::Ladder* ladder = dynamic_cast<const MML::Ladder*>(mml);
    assert(0 != ladder);
    Core::Layer* layer = dynamic_cast<Core::Layer*>(p);
    assert(0 != layer);
    return new Ladder(ladder, layer);
}

} // namespace Assets

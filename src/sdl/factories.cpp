#include "factories.hpp"
#include "gui_object.hpp"
#include "type_manager.hpp"

#include <core/components.hpp>
#include <core/logic_object.hpp>
#include <core/rectangle.hpp>
#include <core/position.hpp>
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
    Core::LogicObject* logicObject = new Core::LogicObject();
    logicObject->setPosition(Core::Position(box->position().first, box->position().second));
    Core::Collider* collider = new Core::Collider();
    collider->setSizes(box->width(), box->height());
    logicObject->addComponent(collider);
    Core::GuiObject* guiObject = new Sdl::GuiObject(box->texture());
    Core::TextureRenderer* textureRenderer = new Core::TextureRenderer();
    textureRenderer->addObserver(guiObject);
    logicObject->addComponent(textureRenderer);
    guiObject->setDimensions(box->width()
            , box->height()
            , textureRenderer->scaleFactor());
    l->addGuiObject(guiObject);
    l->addLogicObject(logicObject);
    return 0;
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
    Core::LogicObject* logicObject = new Core::LogicObject();
    logicObject->setPosition(Core::Position(dude->position().first, dude->position().second));
    Core::Collider* collider = new Core::Collider();
    collider->setSizes(dude->width(), dude->height());
    logicObject->addComponent(collider);
    Core::Physics* physics = new Core::Physics();
    logicObject->addComponent(physics);
    Core::GuiObject* guiObject = new Sdl::GuiObject(dude->texture());
    Core::TextureRenderer* textureRenderer = new Core::TextureRenderer();
    textureRenderer->addObserver(guiObject);
    logicObject->addComponent(textureRenderer);
    guiObject->setDimensions(dude->width()
            , dude->height()
            , textureRenderer->scaleFactor());
    layer->addGuiObject(guiObject);
    layer->addLogicObject(logicObject);
    return 0;
}

} // namespace Sdl

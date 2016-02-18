#ifndef _SDL_FACTORIES_HPP_
#define _SDL_FACTORIES_HPP_

#include <core/controls.hpp>
#include <core/gui.hpp>
#include <core/layer.hpp>
#include <core/logic.hpp>
#include <core/objects_factory.hpp>
#include <mml/mml_object.hpp>
#include <mml/mml_layer.hpp>

#include <cassert>

namespace Sdl
{

class LayerFactory
    : public Core::ObjectsFactory
{
public:
    virtual Core::Layer* create(const MML::MMLObject* mml, Core::Gui* = 0, Core::Logic* = 0) const
    {
        const MML::MMLLayer* mml_layer = dynamic_cast<const MML::MMLLayer*>(mml);
        assert(0 != mml_layer);
        Core::Gui* gui = new Core::Gui();
        Core::Logic* logic = new Core::Logic();
        Core::Layer* layer = new Core::Layer(gui, logic, Core::Controls());
        // TODO get attributes from mml_layer and set on layer
        TypeManager* tm = TypeManager::getInstance();
        assert(0 != tm);
        typedef MML::MMLObject::MMLChildren Children;
        const Children& children = mml_layer->getChildren();
        for(auto obj : children) {
            assert(0 != obj);
            const Core::ObjectsFactory* f = tm->getFactory(obj->getType());
            assert(0 != f);
            f->create(obj, gui, logic); // TODO some how get layers from here
        }
        return layer;
    }
};

} // namespace Sdl

#endif // _SDL_FACTORIES_HPP_

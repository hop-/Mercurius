#include "mercurius.hpp"
#include "event_manager.hpp"
#include "type_manager.hpp"

#include <core/game.hpp>
#include <core/gui.hpp>
#include <core/objects_factory.hpp>
#include <core/layer.hpp>
#include <mml/mml_manager.hpp>
#include <mml/mml_registery.hpp>
#include <sdl/frame.hpp>

namespace Sdl
{

void Mercurius::start()
{
    Core::Frame* frame = new Sdl::Frame;
    Core::EventManager* eventManager = new Sdl::EventManager;
    Core::Game game(frame, eventManager);
    loadLayers(game, frame);
    game.start();
}

void Mercurius::loadLayers(Core::Game& game, Core::Frame* frame)
{
    typedef MML::MMLManager manager;
    manager* m = manager::getInstance();
    assert(0 != m);
    assert(0 != frame);
    m->loadData("src/mml/test/frame.mml");
    MML::MMLRegistery* layer_registery = m->getLayerRegistery();
    assert(0 != layer_registery);
    TypeManager* tm = TypeManager::getInstance();
    assert(0 != tm);
    for(MML::MMLRegistery::iterator i = layer_registery->begin();
                                    i != layer_registery->end(); ++i) {
        MML::MMLObject* layer = *i;
        assert(0 != layer);
        const Core::ObjectsFactory* f = tm->getFactory(layer->getType());
        assert(0 != f);
        Core::Layer* l = f->create(layer);
        assert(0 != l);
        assert(0 != l->gui());
        l->gui()->setFrame(frame); // TODO pase frame before creating child widgets
        game.pushLayer(l); // TODO some how get layers from here
    }
}

} // namespace Sdl

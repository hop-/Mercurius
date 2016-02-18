#include "mercurius.hpp"
#include "event_generator.hpp"
#include "type_manager.hpp"

#include <core/game.hpp>
#include <core/objects_factory.hpp>
#include <mml/mml_manager.hpp>
#include <mml/mml_registery.hpp>
#include <sdl/frame.hpp>

namespace Sdl
{

void Mercurius::start()
{
    Core::Frame* frame = new Sdl::Frame;
    Core::EventGenerator* eventGenerator = new Sdl::EventGenerator;
    Core::Game game(frame, eventGenerator);
    loadLayers(game);
    game.start();
}

void Mercurius::loadLayers(Core::Game& game)
{
    typedef MML::MMLManager manager;
    manager* m = manager::getInstance();
    assert(0 != m);
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
        game.pushLayer(f->create(layer)); // TODO some how get layers from here
    }
}

} // namespace Sdl

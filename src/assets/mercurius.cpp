#include "mercurius.hpp"
#include "type_manager.hpp"

#include <base/utility.hpp>
#include <core/game.hpp>
#include <core/gui.hpp>
#include <core/objects_factory.hpp>
#include <core/layer.hpp>
#include <mml/config.hpp>
#include <mml/mml_manager.hpp>
#include <mml/mml_registery.hpp>
#include <sdl/event_manager.hpp>
#include <sdl/frame.hpp>

namespace Assets
{

Mercurius::Configs Mercurius::m_configs;

void Mercurius::start()
{
    loadConfigs();
    Core::Frame* frame = new Sdl::Frame;
    //TODO TMP begin
    Config* c = m_configs[0];
    assert(0 != c);
    frame->setScreenMode(c->m_screenMode);
    frame->setResolution(c->m_width, c->m_height);
    Core::InputManager::reset();
    Core::InputManager::setMappings(c->m_mapping);
    //TODO TMP end
    Base::InputHandler* inputHandler = new Sdl::InputHandler;
    Core::Game* game = Core::Game::getInstance(frame, inputHandler);
    loadLayers(*game, frame);
    game->start();
    bool r = Core::Game::deleteInstance();
    assert(r);
    r = MML::MMLManager::deleteInstance();
    assert(r);
    r = TypeManager::deleteInstance();
    assert(r);
    Base::Utility::ignoreUnused(r);
}

void Mercurius::loadConfigs()
{
    typedef MML::MMLManager manager;
    manager* m = manager::getInstance();
    assert(0 != m);
    m->loadData("resources/mmls/config.mml");
    MML::MMLRegistery* registery = m->getRegistery();
    assert(0 != registery);
    TypeManager* tm = TypeManager::getInstance();
    assert(0 != tm);
    for(MML::MMLRegistery::iterator i = registery->begin();
                                    i != registery->end(); ++i) {
        MML::MMLObject* config = *i;
        assert(0 != config);
        addConfig(*i);
    }

}

void Mercurius::loadLayers(Core::Game& game, Core::Frame* frame)
{
    typedef MML::MMLManager manager;
    manager* m = manager::getInstance();
    assert(0 != m);
    assert(0 != frame);
    m->loadData("resources/mmls/main.mml");
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
        Base::Object* o = f->create(layer);
        assert(0 != o);
        Core::Layer* l = dynamic_cast<Core::Layer*>(o);
        assert(0 != l);
        assert(0 != l->gui());
        l->gui()->setFrame(frame); // TODO pase frame before creating child widgets
        game.pushLayer(l); // TODO some how get layers from here
    }
}

void Mercurius::addConfig(const MML::MMLObject* config)
{
    assert(0 != config);
    const MML::Config* c = dynamic_cast<const MML::Config*>(config);
    assert(0 != c);
    Config* newConfig = new Config();
    newConfig->m_screenMode = c->screenMode();
    newConfig->m_width = c->resolution().first;
    newConfig->m_height = c->resolution().second;
    newConfig->m_isDefault = c->isDefault();
    std::fill_n(newConfig->m_mapping, 256, Key::None);
    newConfig->m_mapping[c->left()] = Key::Left;
    newConfig->m_mapping[c->right()] = Key::Right;
    newConfig->m_mapping[c->up()] = Key::Up;
    newConfig->m_mapping[c->down()] = Key::Down;
    newConfig->m_mapping[c->jump()] = Key::Jump;
    m_configs.push_back(newConfig);
}

} // namespace Assets

#ifndef _ASSETS_GAME_HPP_
#define _ASSETS_GAME_HPP_

#include <core/service.hpp>
#include "type_manager.hpp"

#include <base/utility.hpp>
#include <core/game.hpp>
#include <core/gui.hpp>
#include <core/objects_factory.hpp>
#include <core/layer.hpp>
#include <mml/config.hpp>
#include <mml/mml_layer.hpp>
#include <mml/mml_manager.hpp>
#include <mml/mml_registery.hpp>
#include <sdl/event_manager.hpp>
#include <sdl/frame.hpp>

namespace Assets
{

class Game : public Core::SingletonService<Game>
{
private:
    struct Config
    {
        Core::Frame::ScreenMode m_screenMode;
        int m_fps;
        int m_width;
        int m_height;
        bool m_isDefault;
        Core::InputManager::Key m_mapping[256];
    };

private:
    typedef Core::InputManager::Key Key;
    typedef std::vector<Config*> Configs;
    static Configs m_configs;

private:
    virtual void start()
    {
        loadConfigs();
        Core::Frame* frame = new Sdl::Frame;
        //TODO TMP begin
        Config* c = m_configs[0];
        assert(0 != c);
        frame->setScreenMode(c->m_screenMode);
        frame->setResolution(c->m_width, c->m_height);
        frame->setFPS(c->m_fps);
        Core::InputManager::reset();
        Core::InputManager::setMappings(c->m_mapping);
        //TODO TMP end
        Base::InputHandler* inputHandler = new Sdl::InputHandler;
        Core::Game* game = Core::Game::getInstance(frame, inputHandler);
        loadLayers(*game, frame);
        game->start();
    }

    virtual void stop()
    {
    }

    virtual void registerDependencies()
    {
        requireDependency<MML::MMLManager>();
        requireDependency<TypeManager>();
    }

    void loadConfigs()
    {
        typedef MML::MMLManager manager;
        manager* m = manager::getInstance();
        assert(0 != m);
        m->loadData("resources/mmls/config.mml");
        MML::MMLRegistery* registery = m->getRegistery();
        assert(0 != registery);
        typedef std::vector<MML::Config*> Configs;
        Configs configs;
        registery->getObjects(configs);
        for(Configs::iterator i = configs.begin();
                i != configs.end(); ++i) {
            MML::Config* config = *i;
            assert(0 != config);
            addConfig(config);
        }

    }

    void loadLayers(Core::Game& game, Core::Frame* frame)
    {
        typedef MML::MMLManager manager;
        manager* m = manager::getInstance();
        assert(0 != m);
        assert(0 != frame);
        m->loadData("resources/mmls/main.mml");
        MML::MMLRegistery* r = m->getRegistery();
        assert(0 != r);
        typedef std::vector<MML::MMLLayer*> Layers;
        Layers layers;
        r->getObjects(layers);
        TypeManager* tm = TypeManager::getInstance();
        assert(0 != tm);
        for(Layers::iterator i = layers.begin();
                i != layers.end(); ++i) {
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

    void addConfig(const MML::Config* c)
    {
        assert(0 != c);
        Config* newConfig = new Config();
        newConfig->m_screenMode = c->screenMode();
        newConfig->m_fps = c->fps();
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

};

Game::Configs Game::m_configs;

} // end of namespace Assets

#endif // _ASSETS_GAME_HPP_

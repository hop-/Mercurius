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
    virtual void start();
    virtual void stop();
    virtual void registerDependencies();
    void loadConfigs();
    void loadLayers(Core::Game& game, Core::Frame* frame);
    void addConfig(const MML::Config* c);
};

} // end of namespace Assets

#endif // _ASSETS_GAME_HPP_

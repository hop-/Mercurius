#ifndef _ASSETS_MERCURIUS_HPP_
#define _ASSETS_MERCURIUS_HPP_

#include <core/frame.hpp>
#include <core/game.hpp>

#include <vector>

namespace MML {

class MMLObject;

}

namespace Assets
{

class Mercurius
{
public:
    static void start();

private:
    struct Config
    {
        Core::Frame::ScreenMode m_screenMode;
        int m_width;
        int m_height;
        bool m_isDefault;
    };

private:
    typedef std::vector<Config*> Configs;
    static Configs m_configs;

private:
    static void addConfig(const MML::MMLObject*);
    static void loadConfigs();
    static void loadLayers(Core::Game&, Core::Frame*);
};

} // namespace Assets

#endif // _ASSETS_MERCURIUS_HPP_

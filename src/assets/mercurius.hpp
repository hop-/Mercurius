#ifndef _ASSETS_MERCURIUS_HPP_
#define _ASSETS_MERCURIUS_HPP_

#include <core/game.hpp>

namespace Assets
{

class Mercurius
{
public:
    static void start();

private:
    static void loadConfigs();
    static void loadLayers(Core::Game&, Core::Frame*);
};

} // namespace Assets

#endif // _ASSETS_MERCURIUS_HPP_

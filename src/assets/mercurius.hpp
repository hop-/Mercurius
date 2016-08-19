#ifndef _ASSETS_MERCURIUS_HPP_
#define _ASSETS_MERCURIUS_HPP_

#include <core/application.hpp>
#include <core/frame.hpp>
#include <core/game.hpp>
#include <core/input_manager.hpp>

#include <vector>

namespace MML {

class Config;

}

namespace Assets
{

class Mercurius : public Core::Application
{
public:
    static void start();

public:
    virtual void startServices();

    virtual ~Mercurius();

};

} // namespace Assets

#endif // _ASSETS_MERCURIUS_HPP_

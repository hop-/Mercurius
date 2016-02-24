#ifndef _SDL_FACTORIES_HPP_
#define _SDL_FACTORIES_HPP_

#include <core/controls.hpp>
#include <core/gui.hpp>
#include <core/layer.hpp>
#include <core/logic.hpp>
#include <core/objects_factory.hpp>
#include <mml/mml_object.hpp>

#include <cassert>

namespace Sdl
{

class LayerFactory
    : public Core::ObjectsFactory
{
public:
    virtual Core::Layer* create(const MML::MMLObject* mml,
                                Core::Gui* = 0,
                                Core::Logic* = 0) const;
};

class BoxFactory
    : public Core::ObjectsFactory
{
public:
    virtual Core::Layer* create(const MML::MMLObject* mml,
                                Core::Gui* gui,
                                Core::Logic* logic) const;
};

} // namespace Sdl

#endif // _SDL_FACTORIES_HPP_

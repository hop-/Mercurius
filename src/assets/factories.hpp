#ifndef _ASSETS_FACTORIES_HPP_
#define _ASSETS_FACTORIES_HPP_

#include <core/gui.hpp>
#include <core/layer.hpp>
#include <core/logic.hpp>
#include <core/objects_factory.hpp>
#include <mml/mml_object.hpp>

#include <cassert>

namespace Assets
{

class LayerFactory
    : public Core::ObjectsFactory
{
public:
    /// Reimplemented interface
    virtual Base::Object* create(const MML::MMLObject* mml,
                                Base::Object* = 0) const;
};

class BoxFactory
    : public Core::ObjectsFactory
{
public:
    /// Reimplemented interface
    virtual Base::Object* create(const MML::MMLObject* mml,
                                Base::Object* p) const;
};

class DudeFactory
    : public Core::ObjectsFactory
{
public:
    /// Reimplemented interface
    virtual Base::Object* create(const MML::MMLObject* mml,
                                Base::Object* p) const;
};

class DoorFactory
    : public Core::ObjectsFactory
{
public:
    /// Reimplemented interface
    virtual Base::Object* create(const MML::MMLObject* mml,
                                Base::Object* p) const;
};

class GroundFactory
    : public Core::ObjectsFactory
{
public:
    /// Reimplemented interface
    virtual Base::Object* create(const MML::MMLObject* mml,
                                Base::Object* p) const;
};

class BackgroundFactory
    : public Core::ObjectsFactory
{
public:
    /// Reimplemented interface
    virtual Base::Object* create(const MML::MMLObject* mml,
                                Base::Object* p) const;

};

class LadderFactory
    : public Core::ObjectsFactory
{
public:
    /// Reimplemented interface
    virtual Base::Object* create(const MML::MMLObject* mml,
                                Base::Object* p) const;
};

} // namespace Assets

#endif // _ASSETS_FACTORIES_HPP_

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
    Base::Object* create(const MML::MMLObject* mml,
                         Base::Object* = 0) const override;
};

class BoxFactory
    : public Core::ObjectsFactory
{
public:
    /// Reimplemented interface
    Base::Object* create(const MML::MMLObject* mml,
                         Base::Object* p) const override;
};

class BeingFactory
    : public Core::ObjectsFactory
{
public:
    /// Reimplemented interface
    Base::Object* create(const MML::MMLObject* mml,
                         Base::Object* p) const override;
};

class DudeFactory
    : public Core::ObjectsFactory
{
public:
    /// Reimplemented interface
    Base::Object* create(const MML::MMLObject* mml,
                         Base::Object* p) const override;
};

class DoorFactory
    : public Core::ObjectsFactory
{
public:
    /// Reimplemented interface
    Base::Object* create(const MML::MMLObject* mml,
                         Base::Object* p) const override;
};

class SwitchFactory
    : public Core::ObjectsFactory
{
public:
    /// Reimplemented interface
    Base::Object* create(const MML::MMLObject* mml,
                         Base::Object* p) const override;
};

class GroundFactory
    : public Core::ObjectsFactory
{
public:
    /// Reimplemented interface
    Base::Object* create(const MML::MMLObject* mml,
                         Base::Object* p) const override;
};

class PlatformFactory
    : public Core::ObjectsFactory
{
public:
    /// Reimplemented interface
    Base::Object* create(const MML::MMLObject* mml,
                         Base::Object* p) const override;
};

class BackgroundFactory
    : public Core::ObjectsFactory
{
public:
    /// Reimplemented interface
    Base::Object* create(const MML::MMLObject* mml,
                         Base::Object* p) const override;

};

class LadderFactory
    : public Core::ObjectsFactory
{
public:
    /// Reimplemented interface
    Base::Object* create(const MML::MMLObject* mml,
                         Base::Object* p) const override;
};

} // namespace Assets

#endif // _ASSETS_FACTORIES_HPP_

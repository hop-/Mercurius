#ifndef _CORE_OBJECTS_FACTORY_HPP_
#define _CORE_OBJECTS_FACTORY_HPP_

namespace MML
{
class MMLObject;
}

namespace Core
{

class Gui;
class Layer;
class Logic;

class ObjectsFactory
{
public:
    virtual Layer* create(const MML::MMLObject*, Gui* = 0, Logic* = 0) const = 0; // TODO need to change the interface
};

} // namespace core

#endif // _CORE_OBJECTS_FACTORY_HPP_

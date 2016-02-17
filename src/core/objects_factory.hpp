#ifndef _CORE_OBJECTS_FACTORY_HPP_
#define _CORE_OBJECTS_FACTORY_HPP_

namespace MML
{
class MMLObject;
}

namespace Core
{

class ObjectsFactory
{
public:
    virtual void create(const MML::MMLObject*) = 0; // TODO need to change the interface
};

} // namespace core

#endif // _CORE_OBJECTS_FACTORY_HPP_

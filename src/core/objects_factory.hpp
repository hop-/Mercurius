#ifndef _CORE_OBJECTS_FACTORY_HPP_
#define _CORE_OBJECTS_FACTORY_HPP_

namespace MML
{
class MMLObject;
}

namespace Base
{
class Object;
}

namespace Core
{

class ObjectsFactory
{
public:
    /**
     * @brief Interface for createing base objects from MML
     * @param m MML object pointer
     * @param p parent for created object
     * @return created object
     * @note m should be valid pointer
     * @note p should be valid pointer
     */
    virtual Base::Object* create(const MML::MMLObject* m, Base::Object* p = 0) const = 0;
};

} // namespace core

#endif // _CORE_OBJECTS_FACTORY_HPP_

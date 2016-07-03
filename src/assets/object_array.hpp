#ifndef _ASSETS_OBJECT_ARRAY_HPP_
#define _ASSETS_OBJECT_ARRAY_HPP_

#include "object.hpp"

namespace MML
{
    class ObjectArray;
}

namespace Assets
{

class ObjectArray
    : public Object
{
public:
    ObjectArray(const MML::ObjectArray* s, Core::Layer* l);

protected:
    void addLogicObject() override;
    const MML::ObjectArray* objectArray() const;

private:
    void addArrayComponent();
};

} // namespace Assets

#endif //_ASSETS_OBJECT_ARRAY_HPP_

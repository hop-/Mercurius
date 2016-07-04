#include "object_array.hpp"

#include <mml/object_array.hpp>
#include <core/components.hpp>

#include <cassert>

namespace Assets
{

ObjectArray::ObjectArray(const MML::ObjectArray* s, Core::Layer* l)
    : Object(s, l)
{}

void ObjectArray::addLogicObject()
{
    Object::addLogicObject();
    addArrayComponent();
}

void ObjectArray::addArrayComponent()
{
    Core::ArrayObject* array = new Core::ArrayObject;
    if (objectArray()->rowsAreAllowed()) {
        array->setRows(objectArray()->rows());
    }
    if (objectArray()->columnsAreAllowed()) {
        array->setColumns(objectArray()->columns());
    }
    addComponent(array);
}

const MML::ObjectArray* ObjectArray::objectArray() const
{
    assert(0 != static_cast<const MML::ObjectArray*>(drawableObject()));
    return static_cast<const MML::ObjectArray*>(drawableObject());
}

} // namespace Assets

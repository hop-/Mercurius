#ifndef _ASSETS_OBJECT_HPP_
#define _ASSETS_OBJECT_HPP_

#include <base/object.hpp>
#include <core/logic_object.hpp>

namespace Core
{

class GuiObject;
class Layer;

}

namespace MML
{
class DrawableObject;
}

namespace Assets
{

class Object : public Base::Object
{
    const MML::DrawableObject* m_drawableObject;
    Core::Layer* m_layer;
    Core::LogicObject* m_logicObject = 0;
    Core::GuiObject* m_guiObject = 0;

public:
    Object(const MML::DrawableObject*, Core::Layer*);

private:
    Object(const Object&) = delete;
    Object& operator=(const Object&) = delete;

protected:
    void init();
    virtual void setupLogicObject() = 0;
    virtual void addGuiObject();
    virtual void addLogicObject();
    virtual void addCollider(bool trigger = false);
    virtual void addPhysics();
    virtual void addComponent(Core::LogicObject::Component* c);
    virtual void addState(Core::State* state);

    const MML::DrawableObject* drawableObject() const;
    Core::Layer* layer();
    Core::LogicObject* logicObject();
    Core::GuiObject* guiObject();
};

} // namespace Assets

#endif // _ASSETS_OBJECT_HPP_

#ifndef _ASSETS_OBJECT_HPP_
#define _ASSETS_OBJECT_HPP_

#include <base/object.hpp>
#include <core/state.hpp>

namespace Core
{
class GuiObject;
class Layer;
class LogicObject;
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

protected:
    void init()
    {
        addLogicObject();
        addGuiObject();
    }
    virtual void setupLogicObject() = 0;
    void addGuiObject();
    void addLogicObject();
    void addCollider();
    void addPhysics();
    void addState(Core::State* state);
    void addMoveable();
};

} // namespace Assets

#endif // _ASSETS_OBJECT_HPP_

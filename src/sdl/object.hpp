#ifndef _SDL_OBJECT_HPP_
#define _SDL_OBJECT_HPP_

#include <base/object.hpp>

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

namespace Sdl
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
    void addGuiObject();
    void addLogicObject();
    void addCollider();
    void addPhysics();
};

} // namespace Sdl

#endif // _SDL_OBJECT_HPP_

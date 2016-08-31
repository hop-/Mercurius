#include "object.hpp"

#include <core/components.hpp>
#include <core/layer.hpp>
#include <core/rectangle.hpp>
#include <core/position.hpp>
#include <core/animation_controller.hpp>
#include <core/data_manager.hpp>

#include <mml/drawable_object.hpp>
#include <sdl/gui_object.hpp>

namespace Assets
{

Object::
Object(const MML::DrawableObject* dr, Core::Layer* layer)
    : m_drawableObject(dr)
    , m_layer(layer)
{
    assert(0 != dr);
    assert(0 != layer);
    layer->addObject(this);
}

void Object::
init()
{
    addLogicObject();
    addGuiObject();
}

void Object::
addGuiObject()
{
    assert(0 == m_guiObject);
    assert(0 != m_drawableObject);
    assert(0 != m_logicObject);
    Core::TextureRenderer* textureRenderer = new Core::TextureRenderer();
    textureRenderer->setSizes(m_drawableObject->width()
            , m_drawableObject->height());
    m_logicObject->addComponent(textureRenderer);
    m_guiObject = new Sdl::GuiObject(textureRenderer, m_drawableObject->texture());
    m_guiObject->setPriority(m_drawableObject->priority());
    m_guiObject->setDimensions(m_drawableObject->width() // TODO use Textu-
            , m_drawableObject->height()                 // ureRendrer dim-
            , textureRenderer->scaleFactor());           // ensions
    assert(0 != m_layer);
    m_layer->addGuiObject(m_guiObject);
}

void Object::
addLogicObject()
{
    assert(0 == m_logicObject);
    assert(0 != m_drawableObject);
    m_logicObject = new Core::LogicObject();
    m_logicObject->addComponent(new Core::Transform);
    m_logicObject->setPosition(m_drawableObject->position().first, m_drawableObject->position().second);
    m_logicObject->setWeight(m_drawableObject->weight());
    m_logicObject->setTypeName(m_drawableObject->getType());
    m_logicObject->setScale(m_drawableObject->scale());
    setupLogicObject();
    assert(0 != m_layer);
    m_layer->addLogicObject(m_logicObject);
    if (m_drawableObject->aimed()) {
        m_layer->aimTo(m_logicObject);
    }
}

void Object::
addCollider(bool trigger)
{
    assert(0 != m_drawableObject);
    assert(0 != m_logicObject);
    Core::Collider* collider = new Core::Collider();
    if (m_drawableObject->body().first == 0
            && m_drawableObject->body().second == 0) { // TODO move to MML
        collider->setSizes(m_drawableObject->width()
                , m_drawableObject->height());
    } else {
        collider->setSizes(m_drawableObject->body().first
                , m_drawableObject->body().second);
    }
    collider->setOffset(m_drawableObject->offset().first,
                m_drawableObject->offset().second);
    collider->trigger(trigger);
    m_logicObject->addComponent(collider);
    addAnimation();
}

void Object::
addPhysics()
{
    assert(0 != m_logicObject);
    Core::Physics* physics = new Core::Physics();
    m_logicObject->addComponent(physics);
}

void Object::
addComponent(Core::LogicObject::Component* c)
{
    assert(0 != c);
    assert(0 != m_logicObject);
    m_logicObject->addComponent(c);
}

void Object::
addState(Core::State* state)
{
    assert(0 != state);
    assert(0 != m_logicObject);
    m_logicObject->addObject(state);
}

void Object::
addAnimation()
{
    auto animations = m_drawableObject->animationList();
    if (0 == animations.size()) {
        return;
    }
    Core::AnimationController* controller = new Core::AnimationController;
    for (const auto& name : animations) {
        assert(0 != Core::DataManager::animationState(name));
        controller->addState(Core::DataManager::animationState(name));
    }
    addComponent(new Core::Animator(controller));
}

const MML::DrawableObject* Object::
drawableObject() const
{
    return m_drawableObject;
}

Core::Layer* Object::
layer()
{
    return m_layer;
}

Core::LogicObject* Object::
logicObject()
{
    return m_logicObject;
}

Core::GuiObject* Object::
guiObject()
{
    return m_guiObject;
}

} // namespace Assets

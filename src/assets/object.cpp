#include "object.hpp"

#include <core/components.hpp>
#include <core/layer.hpp>
#include <core/logic_object.hpp>
#include <core/rectangle.hpp>
#include <core/position.hpp>
#include <mml/drawable_object.hpp>
#include <sdl/gui_object.hpp>

namespace Assets
{

Object::Object(const MML::DrawableObject* dr, Core::Layer* layer)
    : m_drawableObject(dr)
    , m_layer(layer)
{
    assert(0 != dr);
    assert(0 != layer);
    layer->addObject(this);
}

void Object::addGuiObject()
{
    assert(0 == m_guiObject);
    assert(0 != m_drawableObject);
    assert(0 != m_logicObject);
    m_guiObject = new Sdl::GuiObject(m_drawableObject->texture());
    m_guiObject->setPriority(m_drawableObject->priority());
    Core::TextureRenderer* textureRenderer = new Core::TextureRenderer();
    textureRenderer->addObserver(m_guiObject);
    textureRenderer->setScaleFactor(m_drawableObject->scale());
    m_guiObject->setDimensions(m_drawableObject->width()
            , m_drawableObject->height()
            , textureRenderer->scaleFactor());
    m_logicObject->addComponent(textureRenderer);
    assert(0 != m_layer);
    m_layer->addGuiObject(m_guiObject);
}

void Object::addLogicObject()
{
    assert(0 == m_logicObject);
    assert(0 != m_drawableObject);
    m_logicObject = new Core::LogicObject();
    m_logicObject->setPosition(m_drawableObject->position().first, m_drawableObject->position().second);
    m_logicObject->setWeight(m_drawableObject->weight());
    setupLogicObject();
    assert(0 != m_layer);
    m_layer->addLogicObject(m_logicObject);
    if (m_drawableObject->aimed()) {
        m_layer->aimTo(m_logicObject);
    }
}

void Object::addCollider(bool trigger)
{
    assert(0 != m_drawableObject);
    assert(0 != m_logicObject);
    Core::Collider* collider = new Core::Collider();
    collider->setSizes(m_drawableObject->width(), m_drawableObject->height());
    collider->trigger(trigger);
    m_logicObject->addComponent(collider);
}

void Object::addPhysics()
{
    assert(0 != m_logicObject);
    Core::Physics* physics = new Core::Physics();
    m_logicObject->addComponent(physics);
}

void Object::addState(Core::State* state)
{
    assert(0 != state);
    assert(0 != m_logicObject);
    m_logicObject->addObject(state);
}

} // namespace Assets

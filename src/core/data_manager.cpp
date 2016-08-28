#include "data_manager.hpp"
#include "drawable_object.hpp"
#include "animation_state.hpp"

#include <mml/mml_manager.hpp>
#include <mml/mml_registery.hpp>
#include <mml/texture.hpp>
#include <mml/animation.hpp>

#include <debug/log.hpp>

#include <vector>

namespace Core
{

DrawableObject* DataManager::
drawableObject(const std::string& name)
{
    try {
        return m_drawableObjects.at(name);
    } catch (std::out_of_range) {
        return 0;
    }
}

AnimationState* DataManager::
animationState(const std::string& name)
{
    try {
        return m_animationStates.at(name);
    } catch (std::out_of_range) {
        return 0;
    }
}

void DataManager::
registerDependencies()
{
    requireDependency<MML::MMLManager>();
}

void DataManager::
start()
{
    loadTextures();
    loadAnimations();
}

void DataManager::
stop()
{}

void DataManager::
loadTextures()
{
    typedef MML::MMLManager manager;
    manager* m = manager::getInstance();
    assert(0 != m);
    m->loadData("resources/mmls/textures.mml");
    MML::MMLRegistery* registery = m->getRegistery();
    registery = m->getRegistery();
    std::vector<MML::Texture*> textures;
    registery->getObjects(textures);
    for (const auto& texture : textures) {
        auto mr = texture->size();
        auto fr = texture->frameSize();
        m_drawableObjects[texture->getName()] = new DrawableObject(
                    texture->path()
                    , mr.first, mr.second
                    , fr.first, fr.second);
    }
}

void DataManager::
loadAnimations()
{
    typedef MML::MMLManager manager;
    manager* m = manager::getInstance();
    assert(0 != m);
    m->loadData("resources/mmls/animations.mml");
    MML::MMLRegistery* registery = m->getRegistery();
    registery = m->getRegistery();
    std::vector<MML::Animation*> animations;
    registery->getObjects(animations);
    for (const auto& animation : animations) {
        std::string name = animation->getName();
        m_animationStates[name] =
            new AnimationState(name
                    , animation->position()
                    , animation->frameCount()
                    , animation->loop()
                    , animation->fps());
    }
}

} // namespace Core

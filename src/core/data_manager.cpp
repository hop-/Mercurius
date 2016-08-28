#include "data_manager.hpp"
#include "drawable_object.hpp"
#include "animation_controller.hpp"

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

AnimationController* DataManager::
animationController(const std::string& name)
{
    try {
        return m_animationControllers.at(name);
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
        AnimationController* ac = new AnimationController;
        // TODO configure AnimationController
        m_animationControllers[animation->getName()] = ac;
    }
}

} // namespace Core

#ifndef _CORE_DATA_MANAGER_HPP_
#define _CORE_DATA_MANAGER_HPP_

#include "service.hpp"

#include <string>
#include <map>

namespace Core
{

class DrawableObject;
class AnimationState;

class DataManager
    : public SingletonService<DataManager>
{
    using DrawableObjects = std::map<const std::string, DrawableObject*>;
    using AnimationStates = std::map<const std::string, AnimationState*>;

    DrawableObjects m_drawableObjects = DrawableObjects();
    AnimationStates m_animationStates = AnimationStates();

public:
    DrawableObject* drawableObject(const std::string& name);
    AnimationState* animationState(const std::string& name);

private:
    void registerDependencies() override;
    void start() override;
    void stop() override;

private:
    void loadTextures();
    void loadAnimations();
};

} // namespace Core

#endif //_CORE_DATA_MANAGER_HPP_

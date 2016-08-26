#ifndef _CORE_DATA_MANAGER_HPP_
#define _CORE_DATA_MANAGER_HPP_

#include "service.hpp"

#include <string>
#include <map>

namespace Core
{

class DrawableObject;
class AnimationController;

class DataManager
    : public SingletonService<DataManager>
{
    using DrawableObjects = std::map<const std::string, DrawableObject*>;
    using AnimationControllers =
        std::map<const std::string, AnimationController*>;

    DrawableObjects m_drawableObjects = DrawableObjects();
    AnimationControllers m_animationControllers = AnimationControllers();

public:
    DrawableObject* drawableObject(const std::string& name);
    AnimationController* animationController(const std::string& name);

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

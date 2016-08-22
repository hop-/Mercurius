#ifndef _CORE_TEXTURE_LOADER_HPP_
#define _CORE_TEXTURE_LOADER_HPP_

#include "service.hpp"

#include <vector>

namespace Core
{

class DrawableObject;

class TextureLoader
    : public SingletonService<TextureLoader>
{
    using DrawableObjects = std::vector<DrawableObject*>;

    DrawableObjects m_drawableObjects = DrawableObjects();

private:
    void start() override;
    void stop() override;

private:
    void loadTextures();
};

} // namespace Core

#endif //_CORE_TEXTURE_LOADER_HPP_

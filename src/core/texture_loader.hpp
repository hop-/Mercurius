#ifndef _CORE_TEXTURE_LOADER_HPP_
#define _CORE_TEXTURE_LOADER_HPP_

#include "service.hpp"

#include <string>
#include <map>

namespace Core
{

class DrawableObject;

class TextureLoader
    : public SingletonService<TextureLoader>
{
    using DrawableObjects = std::map<const std::string, DrawableObject*>;

    DrawableObjects m_drawableObjects = DrawableObjects();

public:
    DrawableObject* drawableObject(const std::string& name); // Maybe need to
                                                             // move to the new
                                                             // class which will
                                                             // contains all
                                                             // DrawableObjects and
                                                             // will be singleton

private:
    void start() override;
    void stop() override;

private:
    void loadTextures();
};

} // namespace Core

#endif //_CORE_TEXTURE_LOADER_HPP_

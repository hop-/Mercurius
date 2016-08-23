#include "texture_loader.hpp"
#include "drawable_object.hpp"

#include <mml/mml_manager.hpp>
#include <mml/mml_registery.hpp>
#include <mml/texture.hpp>

#include <debug/log.hpp>

#include <vector>

namespace Core
{

DrawableObject* TextureLoader::
drawableObject(const std::string& name)
{
    try {
        return m_drawableObjects.at(name);
    } catch (std::out_of_range) {
        return 0;
    }
}

void TextureLoader::
start()
{
    loadTextures();
}

void TextureLoader::
stop()
{}

void TextureLoader::
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

} // namespace Core

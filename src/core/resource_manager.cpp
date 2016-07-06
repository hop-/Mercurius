#include "resource_manager.hpp"

namespace Core
{

template<>
ResourceManager* Base::Singleton<ResourceManager>::m_s_instance = 0;

ResourceManager::Resource::
Resource(std::string fileName)
    : m_fileLocation(fileName)
{
    loadTheFile();
}

ResourceManager::Resource::
~Resource()
{
    if (0 != m_buffer) {
        delete [] m_buffer;
    }
}

void ResourceManager::Resource::
loadTheFile()
{
    // TODO
}

/////////////////////////////////////////////////////////////

ResourceManager::
ResourceManager()
    : m_resourceRoot("") // TODO change to static get/set interface
    , m_textures()
    , m_mmls()
    , m_sounds()
{}

void ResourceManager::
load()
{
    // TODO load textures
    // TODO load mmls?
    // TODO load sounds (in future)
}

ResourceManager::Resource ResourceManager::
texture(const std::string& name) const
{
    return m_textures.at(name);
}

ResourceManager::Resource ResourceManager::
mainMML() const
{
    return m_textures.at(m_mainMML);
}

ResourceManager::Resource ResourceManager::
mml(const std::string& name) const
{
    return m_mmls.at(name);
}

ResourceManager::Resource ResourceManager::
sound(const std::string& name) const
{
    return m_sounds.at(name);
}

} // namespace Core

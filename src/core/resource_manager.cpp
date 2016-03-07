#include "resource_manager.hpp"

namespace Core
{

ResourceManager::Resource::Resource(std::string fileLocation)
    : m_fileLocation(fileLocation)
{
    loadTheFile();
}

ResourceManager::Resource::~Resource()
{
    if (0 != m_buffer) {
        delete [] m_buffer;
    }
}

void ResourceManager::Resource::loadTheFile()
{
    // TODO
}

/////////////////////////////////////////////////////////////

ResourceManager::ResourceManager(std::string resourceRoot)
    : m_resourceRoot(resourceRoot)
{}

void ResourceManager::load()
{
    // TODO load textures
    // TODO load mmls?
    // TODO load sounds (in future)
}

} // namespace Core

#ifndef _CORE_RESOURCE_MANAGER_HPP_
#define _CORE_RESOURCE_MANAGER_HPP_

#include <base/singleton.hpp>

#include <string>
#include <map>

namespace Core
{

class ResourceManager : public Base::Singleton<ResourceManager>
{
public:
    class Resource
    {
        const std::string m_fileLocation;
        char* m_buffer = 0;
        int m_size = 0;

    public:
        Resource(std::string fileName);
        ~Resource();

        std::string fileLocation() const
        {
            return m_fileLocation;
        }

        const char* buffer() const
        {
            return m_buffer;
        }

        int size() const
        {
            return m_size;
        }

    public:
        Resource(const Resource&) = default; // TODO pointer?
        Resource& operator=(const Resource&) = default;

    private:
        void loadTheFile();
    };

private:
    const std::string m_resourceRoot = "resources";

    const std::string m_textureDir = "textures";
    const std::string m_mmlDir = "mmls";

    const std::string m_mmlExtension = "mml";
    const std::string m_textureExtension = "png";

    const std::string m_mainMML = "main";

    std::map<std::string, Resource> m_textures;
    std::map<std::string, Resource> m_mmls;
    std::map<std::string, Resource> m_sounds;

public:
    ResourceManager();

public:
    void load();
    Resource texture(const std::string& name) const;
    Resource mainMML() const;
    Resource mml(const std::string& name) const;
    Resource sound(const std::string& name) const;

private:
    friend class Base::Singleton<ResourceManager>;
};

} // namespace Core

#endif //_CORE_RESOURCE_MANAGER_HPP_

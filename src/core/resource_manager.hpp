#ifndef _CORE_RESOURCE_MANAGER_HPP_
#define _CORE_RESOURCE_MANAGER_HPP_

#include <string>
#include <map>

namespace Core
{

class ResourceManager
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

        inline std::string fileLocation() const
        {
            return m_fileLocation;
        }

        inline const char* buffer() const
        {
            return m_buffer;
        }

        inline int size() const
        {
            return m_size;
        }

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
    ResourceManager() = default;

public:
    ResourceManager(std::string resourceRoot);

public:
    void load();
    inline Resource texture(const std::string& name) const
    {
        return m_textures.at(name);
    }

    inline Resource mainMML() const
    {
        return m_mmls.at(m_mainMML);
    }

    inline Resource mml(const std::string& name) const
    {
        return m_mmls.at(name);
    }

    inline Resource sound(const std::string& name) const
    {
        return m_sounds.at(name);
    }
};

} // namespace Core

#endif //_CORE_RESOURCE_MANAGER_HPP_

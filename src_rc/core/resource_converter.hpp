#ifndef _CORE_RESOURCE_CONVERTER_HPP_
#define _CORE_RESOURCE_CONVERTER_HPP_

#include <string>

namespace Core
{

class ResourceConverter
{
    std::string m_resourceRoot;
    std::string m_outputName = "resources.rs";

    const std::string m_textureDir = "textures";
    const std::string m_mmlDir = "mmls";

    const std::string m_mmlExtension = "mml";
    const std::string m_textureExtension = "png";

public:
    ResourceConverter(std::string resourceRoot);
    void convert();
};

} // namespace Core

#endif //_CORE_RESOURCE_CONVERTER_HPP_

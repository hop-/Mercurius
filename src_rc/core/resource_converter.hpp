#ifndef _CORE_RESOURCE_CONVERTER_HPP_
#define _CORE_RESOURCE_CONVERTER_HPP_

#include <string>
#include <map>
#include <vector>

namespace Core
{

class ResourceConverter
{
    std::string m_resourceRoot;
    std::string m_outputName = "resources.rs";
    std::map<std::string, int> m_resourceTypesAndCounts;
    std::map<std::string, int> m_resourceNamesAndSizes;
    std::string m_data;
    std::string m_fullContent;

public:
    ResourceConverter(std::string resourceRoot);
    void convert();

private:
    void load(std::string dir
            , std::string fileName
            , std::string ext);
    void collect();
    void compress();
    void encrypt();
    void write();
};

} // namespace Core

#endif //_CORE_RESOURCE_CONVERTER_HPP_

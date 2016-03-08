#include "resource_converter.hpp"

#include <vector>
#include <dirent.h>
#include <fstream>
#include <sstream>

namespace Core
{

namespace
{

static const std::string dirSeparator = "/";

static const std::string textureDir = "textures";
static const std::string mmlDir = "mmls";

static const std::string mmlExtension = "mml";
static const std::string textureExtension = "png";

std::vector<std::string> listResources(const std::string& root
        , const std::string& dirName
        , const std::string& ext)
{
    std::vector<std::string> resourceList;
    std::string dirLocation = root + dirSeparator + dirName;
    DIR* dir = opendir(dirLocation.c_str());
    if (0 == dir) {
        return resourceList; // TODO throw an exception
    }
    dirent* ent = readdir(dir);
    while (0 != ent) {
        std::string fileName = ent->d_name;
        if (fileName.substr(fileName.find_last_of(".") + 1) == ext) {
            resourceList.push_back(
                    fileName.substr(0, fileName.find_last_of(".")));
        }
        ent = readdir(dir);
    }
    closedir (dir);
    return resourceList;
}

} // namespace {anonymus}

ResourceConverter::ResourceConverter(std::string resourceRoot)
    : m_resourceRoot(resourceRoot)
{}

void ResourceConverter::convert()
{
    for (auto file : listResources(m_resourceRoot
                , textureDir
                , textureExtension)) {
        load(textureDir, file, textureExtension);
    }
    for (auto file : listResources(m_resourceRoot
                , mmlDir
                , mmlExtension)) {
        load(textureDir, file, mmlExtension);
    }
    collect();
    compress();
    encrypt();
    write();
}

void ResourceConverter::load(std::string dir
        , std::string fileName
        , std::string ext)
{
    ++m_resourceTypesAndCounts[dir];
    std::string fileLocation = m_resourceRoot
        + dirSeparator // '/'
        + dir
        + dirSeparator // '/'
        + fileName
        + "."
        + ext;
    std::ifstream file(fileLocation, std::ios::binary);
    if (!file.is_open()) {
        return; // TODO throw an exception
    }
    std::ostringstream oss;
    oss << file.rdbuf();
    file.close();
    m_data += oss.str();
    m_resourceNamesAndSizes[fileName] = oss.str().size();
}

void ResourceConverter::collect()
{
    // TODO collect data into one buffer
}

void ResourceConverter::compress()
{
    // TODO compress buffer
}

void ResourceConverter::encrypt()
{
    // TODO encrypt buffer
}

void ResourceConverter::write()
{
    // TODO write buffer into file
}

} // namespace Core

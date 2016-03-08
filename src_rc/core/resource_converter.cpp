#include "resource_converter.hpp"

#include <vector>
#include <fstream>
#include <sstream>

#include <dirent.h>
#include <zlib.h>
#include <cstring>

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
        load(mmlDir, file, mmlExtension);
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
    // TODO is this methode cross system?
    m_fullContent = "";
    int i = m_resourceTypesAndCounts.size();
    if (0 == i) {
        return;
    }
    m_fullContent += (char*)&i;
    for (auto pair : m_resourceTypesAndCounts) {
        i = pair.first.size();
        m_fullContent += (char*)&i;
        m_fullContent += (char*)&pair.first;
        m_fullContent += (char*)&pair.second;
    }
    for (auto pair : m_resourceNamesAndSizes) {
        i = pair.first.size();
        m_fullContent += (char*)&i;
        m_fullContent += (char*)&pair.first;
        m_fullContent += (char*)&pair.second;
    }
    m_fullContent += m_data;
}

void ResourceConverter::compress()
{
    // copied from https://panthema.net/2007/0328-ZLibString.html
    int compressionlevel = Z_BEST_COMPRESSION;
    z_stream zs;
    memset(&zs, 0, sizeof(zs));
    if (deflateInit(&zs, compressionlevel) != Z_OK) {
        return;  // TODO throw exception
    }
    zs.next_in = (Bytef*)m_fullContent.data();
    zs.avail_in = m_fullContent.size();
    int ret;
    char outbuffer[32768]; // may cotain issue
    std::string outstring;
    do {
        zs.next_out = reinterpret_cast<Bytef*>(outbuffer);
        zs.avail_out = sizeof(outbuffer);

        ret = deflate(&zs, Z_FINISH);

        if (outstring.size() < zs.total_out) {
            outstring.append(outbuffer,
                    zs.total_out - outstring.size());
        }
    } while (ret == Z_OK);
    deflateEnd(&zs);
    if (ret != Z_STREAM_END) {
        return;
    }
    m_fullContent = outstring;
}

void ResourceConverter::encrypt()
{
    // TODO encrypt buffer
}

void ResourceConverter::write()
{
    std::ofstream outFile(m_outputName);
    if (!outFile.is_open()) {
        return; // TODO throw an exception
    }
    outFile << m_fullContent;
    outFile.close();
}

} // namespace Core

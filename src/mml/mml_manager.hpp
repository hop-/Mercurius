#ifndef _MML_MMLMANAGER_HPP
#define _MML_MMLMANAGER_HPP

#include "mml_object.hpp"

#include <map>
#include <string>

namespace MML
{

class MMLRegistery;

class MMLManager
{
    static MMLManager* m_instance;

private:
    MMLRegistery* m_registery;
    MMLRegistery* m_layer_registery;
    typedef MMLObject::AbstractFactory Factory;
    typedef std::map<std::string, Factory*> Types;
    Types m_types;

public:
    static MMLManager* getInstance();
    static bool deleteInstance();

public:
    MMLManager();
    ~MMLManager();

public:
    bool loadData(const std::string&);

public:
    MMLRegistery* getRegistery();

public:
    MMLRegistery* getLayerRegistery();

private:
    Factory* getTypeFactory(const std::string&);

private:
    void registerTypes();
    void cleanTypeRegistery();

private:
    MMLManager(const MMLManager&) = delete;
    MMLManager& operator=(const MMLManager&) = delete;

    friend class MMLParser;
};

} // namespace MML

#endif // _MML_MMLMANAGER_HPP

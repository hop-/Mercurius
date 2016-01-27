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
    typedef MMLObject::AbstractFactory Factory;
    typedef std::map<std::string, Factory*> Types;
    Types m_types;

public:
    static MMLManager* getInstance();

public:
    MMLManager();
    ~MMLManager();

public:
    bool parseMMLFile(const std::string&);

public:
    MMLRegistery* getRegistery();

private:
    Factory* getTypeFactory(const std::string&);

private:
    void registerTypes();
    void cleanTypeRegistery();

private:
    MMLManager(const MMLManager&) = delete;
    MMLManager& operator=(const MMLManager&) = delete;
};

} // namespace MML

#endif // _MML_MMLMANAGER_HPP

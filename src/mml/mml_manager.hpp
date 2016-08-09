#ifndef _MML_MMLMANAGER_HPP
#define _MML_MMLMANAGER_HPP

#include "mml_object.hpp"

#include <base/singleton.hpp>

#include <map>
#include <string>

namespace MML
{

class MMLRegistery;

class MMLManager : public Base::Singleton<MMLManager>
{
private:
    MMLRegistery* m_registery;
    typedef MMLObject::AbstractFactory Factory;
    typedef std::map<std::string, Factory*> Types;
    Types m_types;

private:
    MMLManager();
    virtual ~MMLManager();

public:
    bool loadData(const std::string&);

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

    friend class MMLParser;
    friend class Base::Singleton<MMLManager>;
};

} // namespace MML

#endif // _MML_MMLMANAGER_HPP

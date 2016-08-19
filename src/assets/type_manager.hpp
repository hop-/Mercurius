#ifndef _ASSETS_TYPE_MANAGER_HPP_
#define _ASSETS_TYPE_MANAGER_HPP_

#include <core/service.hpp>

#include <map>
#include <string>

namespace Core
{
class ObjectsFactory;
}

namespace Assets
{

class TypeManager : public Core::SingletonService<TypeManager>
{
private:
    typedef std::map<std::string, Core::ObjectsFactory*> Factories;
    Factories m_factories;

public:
    const Core::ObjectsFactory* getFactory(const std::string& type) const;

private:
    virtual void registerDependencies();

private:
    virtual void start();
    virtual void stop();

private:
    TypeManager();

private:
    TypeManager(const TypeManager&) = delete;
    const TypeManager& operator=(const TypeManager&) = delete;

private:
    void registerTypes();

    friend class Base::Singleton<TypeManager>;
};

} // namespace Assets

#endif // _ASSETS_TYPE_MANAGER_HPP_

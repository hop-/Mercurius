#ifndef _SDL_TYPE_MANAGER_HPP_
#define _SDL_TYPE_MANAGER_HPP_

#include <map>
#include <string>

namespace Core
{
class ObjectsFactory;
}

namespace Sdl
{

class TypeManager
{
private:
    std::map<std::string, Core::ObjectsFactory*> m_factories;

private:
    static TypeManager* m_instance;

public:
    static TypeManager* getInstance();

public:
    Core::ObjectsFactory* getFactory(const std::string& type);

private:
    TypeManager();

private:
    TypeManager(const TypeManager&) = delete;
    const TypeManager& operator=(const TypeManager&) = delete;

private:
    void registerTypes();
};

} // namespace Sdl

#endif // _SDL_TYPE_MANAGER_HPP_

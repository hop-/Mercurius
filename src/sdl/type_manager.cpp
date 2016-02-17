#include "type_manager.hpp"

#include <core/objects_factory.hpp>

namespace Sdl
{

TypeManager* TypeManager::m_instance = 0;

TypeManager* TypeManager::getInstance()
{
    if (m_instance == 0) {
        m_instance = new TypeManager();
    }
    return m_instance;
}

TypeManager::TypeManager()
{
    registerTypes();
}

void TypeManager::registerTypes()
{
    // TODO register all types here
}

Core::ObjectsFactory* TypeManager::getFactory(const std::string& type)
{
    // TODO
    return 0;
}

}

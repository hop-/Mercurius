#include "type_manager.hpp"

#include "factories.hpp"

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
    m_factories["layer"] = new LayerFactory();
}

const Core::ObjectsFactory* TypeManager::getFactory(const std::string& type) const
{
    Factories::const_iterator i = m_factories.find(type);
    return i != m_factories.end() ? i->second : 0;
}

}

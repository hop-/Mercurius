#include "type_manager.hpp"

#include "factories.hpp"

namespace Assets
{

template <>
TypeManager* Base::Singleton<TypeManager>::m_s_instance = 0;

TypeManager::TypeManager()
    : Base::Singleton<TypeManager>()
    , m_factories()
{
    registerTypes();
}

void TypeManager::registerTypes()
{
    // TODO register all types here
    m_factories["layer"] = new LayerFactory();
    m_factories["box"] = new BoxFactory();
    m_factories["dude"] = new DudeFactory();
    m_factories["ground"] = new GroundFactory();
    m_factories["background"] = new BackgroundFactory();
    m_factories["ladder"] = new LadderFactory();
}

const Core::ObjectsFactory* TypeManager::getFactory(const std::string& type) const
{
    Factories::const_iterator i = m_factories.find(type);
    return i != m_factories.end() ? i->second : 0;
}

}

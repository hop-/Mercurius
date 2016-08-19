#include "type_manager.hpp"
#include "factories.hpp"

#include <mml/mml_manager.hpp>

namespace Assets
{

TypeManager::
TypeManager()
    : Core::SingletonService<TypeManager>()
    , m_factories()
{
}

void TypeManager::
start()
{
    registerTypes();
}

void TypeManager::
stop()
{
    for (auto i : m_factories) {
        delete i.second;
    }
    m_factories.clear();
}

void TypeManager::
registerDependencies()
{
    requireDependency<MML::MMLManager>();
}

void TypeManager::
registerTypes()
{
    // TODO register all types here
    m_factories["layer"] = new LayerFactory();
    m_factories["box"] = new BoxFactory();
    m_factories["being"] = new BeingFactory();
    m_factories["dude"] = new DudeFactory();
    m_factories["door"] = new DoorFactory();
    m_factories["switch"] = new SwitchFactory();
    m_factories["ground"] = new GroundFactory();
    m_factories["platform"] = new PlatformFactory();
    m_factories["background"] = new BackgroundFactory();
    m_factories["ladder"] = new LadderFactory();
}

const Core::ObjectsFactory* TypeManager::
getFactory(const std::string& type) const
{
    Factories::const_iterator i = m_factories.find(type);
    return i != m_factories.end() ? i->second : 0;
}

}

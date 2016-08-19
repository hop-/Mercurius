#include "controller.hpp"
#include "service.hpp"

namespace Core
{

namespace {

static const Controller::dependencies empty_dependencies;

class CornerStone : public SingletonService<CornerStone>
{
private:
    virtual void start()
    {
    }

    virtual void stop()
    {
    }
};

} // end of unnamed namespace

Controller::
Controller()
    : m_services()
    , m_dependency_map()
    , m_corner_stone_creating(false)
{
}

void Controller::
initCornerStone()
{
    m_corner_stone_creating = true;
    CornerStone::getInstance();
    m_corner_stone_creating = false;
}

bool Controller::
registerService(Service* s)
{
    assert(0 != s);
    if (m_services.find(s->getType()) == m_services.end()) {
        return false;
    }
    m_services[s->getType()] = s;
    if (!m_corner_stone_creating) {
        registerDependency(CornerStone::getInstance()->getType(), s->getType());
    }
    return true;
}

void Controller::
unregisterService(int id)
{
    m_dependency_map.erase(id);
    m_services.erase(id);
}

Service* Controller::
getService(int id)
{
    return m_services[id];
}

bool Controller::
registerDependency(int s, int d)
{
    if (m_services.find(s) == m_services.end() ||
        m_services.find(d) == m_services.end()) {
        return false;
    }
    return m_dependency_map[s].insert(d).second;
}

const Controller::dependencies& Controller::
getDependencies(int id)
{
    const dependency_map::const_iterator i = m_dependency_map.find(id);
    if (i == m_dependency_map.end()) {
        return empty_dependencies;
    }
    return i->second;
}

void Controller::
stopService(int id)
{
    assert(m_services.find(id) != m_services.end());
    while (true) {
        const dependencies& d = getDependencies(id);
        if (d.empty()) {
            break;
        }
        stopService(*d.begin());
    }
    Service* s = getService(id);
    assert(0 != s);
    s->stop();
    s->m_current_state = Service::stopped;
    delete s;
}

Controller::
~Controller()
{
    stopService(CornerStone::getInstance()->getType());
    CornerStone::deleteInstance();
}

} // end of namespace Core

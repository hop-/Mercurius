#ifndef _CORE_CONTROLLER_HPP_
#define _CORE_CONTROLLER_HPP_

#include <base/singleton.hpp>

#include <map>
#include <set>

namespace Core
{

class Service;

class Controller : public Base::Singleton<Controller>
{
public:
    typedef std::set<int> dependencies;
    typedef std::map<int, dependencies> dependency_map;

private:
    typedef std::map<int, Service*> services;
    services m_services;
    dependency_map m_dependency_map;
    bool m_corner_stone_creating;

public:
    Controller();
    virtual ~Controller();

public:
    void initCornerStone();

public:
    bool registerService(Service*);
    bool registerDependency(int, int);
    void unregisterService(int);

public:
    void stopService(int);

public:
    Service* getService(int);

private:
    const dependencies& getDependencies(int);
};

} // end of namespace Core

#endif // _CORE_CONTROLLER_HPP_

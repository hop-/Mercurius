#ifndef _CORE_SERVICE_HPP_
#define _CORE_SERVICE_HPP_

#include <base/singleton.hpp>

namespace Core {

template <typename T>
class Service : public Base::Singleton<T>
{
public:
    Service()
    {
        // TODO register service in controller
    }

public:
    virtual ~Service()
    {
        // TODO unregister service from controller
    }

public:
    void load()
    {
        register_dependencies();
        start();
    }

    void shut_down()
    {
        // TODO stop from controller by checking dependencies
    }

protected:
    virtual void start() = 0;
    virtual void stop() = 0;

public:
    virtual void register_dependencies()
    {}
};

} // end of namespace Core

#endif // _CORE_SERVICE_HPP_

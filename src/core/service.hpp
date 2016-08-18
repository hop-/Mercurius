#ifndef _CORE_SERVICE_HPP_
#define _CORE_SERVICE_HPP_

#include "controller.hpp"

namespace Core {

class Service : public Base::TypedBase
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

public:
    virtual int getType()
    {
        return m_id;
    }

protected:
    virtual void register_dependencies()
    {}

protected:
    virtual void start() = 0;
    virtual void stop() = 0;

private:
    Base::TypedBase::ID m_id;
};

template <typename T>
class Singleton : public Service
                , public Base::Singleton<T>
{
protected:
    template <typename D, typename S = T>
    static bool create_dependency()
    {
        Controller* c = Controller::getInstance();
        assert(0 != c);
        c->register_dependecy(S::getInstance(), D::getInstance());
    }
};

} // end of namespace Core

#endif // _CORE_SERVICE_HPP_

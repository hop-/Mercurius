#ifndef _CORE_SERVICE_HPP_
#define _CORE_SERVICE_HPP_

#include "controller.hpp"

#include <base/typed_base.hpp>
#include <base/singleton.hpp>

namespace Core {

class Service : public Base::TypedBase
{
private:
    Base::TypedBase::ID m_id;

    enum State {stopped = 0, starting, started, max};
    State m_current_state = stopped;

public:
    Service()
        : m_id()
    {
        Controller* c = Controller::getInstance();
        assert(0 != c);
        c->registerService(this);
        // TODO register service in controller
    }

public:
    virtual ~Service()
    {
        Controller* c = Controller::getInstance();
        assert(0 != c);
        c->unregisterService(getType());
    }

public:
    virtual int getType() const
    {
        return m_id;
    }

protected:
    void load()
    {
        assert(m_current_state == stopped);
        m_current_state = starting;
        registerDependencies();
        start();
        m_current_state = started;
    }

private:
    virtual void registerDependencies()
    {}

protected:
    virtual void start() = 0;
    virtual void stop() = 0;

private:
    friend class Controller;

public:
};

template <typename T>
class SingletonService : public Core::Service
                , public Base::Singleton<T>
{
public:
    static T* getInstance()
    {
        T* s = Base::Singleton<T>::getInstance();
        static bool is_instantiated = false;
        if (!is_instantiated) {
            assert(0 != s);
            s->load();
            is_instantiated = true;
        }
        return s;
    }

protected:
    template <typename D>
    bool requireDependency()
    {
        Controller* c = Controller::getInstance();
        assert(0 != c);
        return c->registerDependency(D::getInstance()->getType(), getType());
    }
};

} // end of namespace Core

#endif // _CORE_SERVICE_HPP_

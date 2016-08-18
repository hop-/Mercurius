#ifndef _CORE_SERVICE_HPP_
#define _CORE_SERVICE_HPP_

#include <base/singltone.hpp>

namespace Core {

template <typename T>
class Service : public Base::Singleton<T>
{
public:
    Service();

public:
    virtual ~Service();

public:
    void load();
    void shut_down();

protected:
    virtual void start() = 0;
    virtual void stop() = 0;

public:
    virtual void register_dependencies()
    {}
};

template <typename T>
T* Service::m_s_instance = 0;

} // end of namespace Core

#endif // _CORE_SERVICE_HPP_

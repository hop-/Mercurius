#ifndef _CORE_APPLICATION_HPP_
#define _CORE_APPLICATION_HPP_

#include "controller.hpp"

namespace Core {

class Application
{
public:
    void play()
    {
        startServices();
        Controller::deleteInstance();
    }

public:
    virtual ~Application()
    {}

private:
    virtual void startServices() = 0;

};

} // end of namespace Core

#endif // _CORE_APPLICATION_HPP_

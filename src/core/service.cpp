#include "service.hpp"

namespace Core
{

Service::
Service()
{
// TODO register service in controller
}

Service::
~Service()
{
// TODO unregister service from controller
}

void Service::
load()
{
    register_dependencies();
    start();
}

void Service::
shut_down()
{
// TODO stop from controller by checking dependencies
}

} // end of namespace Core

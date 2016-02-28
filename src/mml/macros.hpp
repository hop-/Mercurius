#ifndef _MML_MACROS_HPP_
#define _MML_MACROS_HPP_

#include "mml_attribute.hpp"

#include <cassert>

#define ATTRIBUTE_INTERFACE(TYPE, ATTR, GET) \
public: \
    TYPE GET() const \
    {\
            const MMLAttribute* attr = getAttribute(ATTR); \
            assert(0 != attr); \
            return attr->getValue<TYPE>(); \
    } 

#endif // _MML_MACROS_HPP_

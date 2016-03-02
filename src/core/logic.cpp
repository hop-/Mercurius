#include "logic.hpp"
#include "logic_object.hpp"

#include <algorithm>

namespace Core
{

void Logic::update()
{
    for (auto* object : children()) {
        assert(0 != object);
        object->update();
    }
}


Logic::Logic()
{
}

Logic::~Logic()
{
}

} // namespace Core 

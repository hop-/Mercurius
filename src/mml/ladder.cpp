#include "ladder.hpp"

namespace MML
{

MMLObject* Ladder::Factory::
create(const std::string& n)
{
    return new Ladder(n);
}

Ladder::
Ladder(const std::string& n)
    : ObjectArray(n)
{
    setType("ladder");
    allowColumns(false);
}

} // namespace MML

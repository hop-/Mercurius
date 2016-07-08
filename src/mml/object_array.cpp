#include "object_array.hpp"

namespace MML
{

ObjectArray::
ObjectArray(const std::string& n)
    : DrawableObject(n)
    , m_allowColunms(true)
    , m_allowRows(true)
{
    addAttribute(new MMLAttribute("rows", 1));
    addAttribute(new MMLAttribute("columns", 1));
}

void ObjectArray::
allowColumns(bool status)
{
    m_allowColunms = status;
}

void ObjectArray::
allowRows(bool status)
{
    m_allowRows = status;
}

bool ObjectArray::
columnsAreAllowed() const
{
    return m_allowColunms;
}

bool ObjectArray::
rowsAreAllowed() const
{
    return m_allowRows;
}

} // namespace MML

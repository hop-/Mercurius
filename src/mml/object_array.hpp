#ifndef _MML_OBJECT_ARRAY_HPP_
#define _MML_OBJECT_ARRAY_HPP_

#include "drawable_object.hpp"

namespace MML
{

class ObjectArray
    : public DrawableObject
{
public:
    ObjectArray(const std::string& n);

public:
    ATTRIBUTE_INTERFACE(int, "rows", rows);
    ATTRIBUTE_INTERFACE(int, "columns", columns);

    bool m_allowColunms;
    bool m_allowRows;

public:
    void allowColumns(bool status);
    void allowRows(bool status);
    bool columnsAreAllowed() const;
    bool rowsAreAllowed() const;
};

} // namespace MML

#endif //_MML_OBJECT_ARRAY_HPP_

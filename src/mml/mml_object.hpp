#ifndef _MML_MML_OBJECT_HPP
#define _MML_MML_OBJECT_HPP

#include <string>

namespace MML
{

class MMLObject
{
public:
    MMLObject() = default;
    virtual ~MMLObjectct()
    {}

public:
    const std::string& get_type() = 0;

};

} // namespace MML

#endif // _MML_MML_OBJECT_HPP

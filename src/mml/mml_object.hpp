#ifndef _MML_MML_OBJECT_HPP
#define _MML_MML_OBJECT_HPP

#include <string>
#include <vector>

namespace MML
{

class MMLAttribute;

class MMLObject
{
public:
    MMLObject() = default;
    virtual ~MMLObject()
    {}

public:
    const std::string& getType() = 0;

public:
    typedef std::vector<MMLAttribute*> MMLAttributes;
    typedef const MMLAttributes CMMLAttributes;

    CMMLAttributes& getAttributes() const;

protected:
    void addAttribute(MMLAttribute*);

private:
    MMLAttributes m_attributes;
};

} // namespace MML

#endif // _MML_MML_OBJECT_HPP

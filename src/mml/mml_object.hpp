#ifndef _MML_MMLOBJECT_HPP
#define _MML_MMLOBJECT_HPP

#include <string>
#include <vector>

namespace MML
{

class MMLAttribute;

class MMLObject
{
public:
    MMLObject(const std::string&, MMLObject* = 0);
    virtual ~MMLObject() = 0;

public:
    const std::string& getType();

public:
    typedef std::vector<MMLAttribute*> MMLAttributes;
    typedef const MMLAttributes CMMLAttributes;

    CMMLAttributes& getAttributes() const;

public:
    const std::string& getName() const;

public:
    void setParent(MMLObject*);
    const MMLObject* getParent() const;

protected:
    void addAttribute(MMLAttribute*);
    void setType(const std::string&);

private:
    MMLAttributes m_attributes;
    const std::string m_name;
    std::string m_type;
    MMLObject* m_parent;
};

} // namespace MML

#endif // _MML_MMLOBJECT_HPP

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
    typedef std::vector<MMLAttribute*> MMLAttributes;
    typedef const MMLAttributes CMMLAttributes;
    typedef std::vector<MMLObject*> MMLChildren;

private:
    MMLAttributes m_attributes;
    std::string m_type;
    MMLObject* m_parent;
    MMLChildren m_children;

public:
    MMLObject(const std::string&, MMLObject* = 0);
    virtual ~MMLObject();

public:
    const std::string& getType() const;

protected:
    CMMLAttributes& getAttributes() const;

public:
    MMLAttribute* getAttribute(const std::string&);
    const MMLAttribute* getAttribute(const std::string&) const;

public:
    const MMLChildren& getChildren() const;

public:
    std::string getName() const;

public:
    void setParent(MMLObject*);
    const MMLObject* getParent() const;

public:
    class AbstractFactory
    {
    public:
        virtual ~AbstractFactory()
        {}
    public:
        virtual MMLObject* create(const std::string&) = 0;
    };

protected:
    void addAttribute(MMLAttribute*);
    void setType(const std::string&);
    void addChild(MMLObject*);
    void removeChild(MMLObject*);
};

} // namespace MML

#endif // _MML_MMLOBJECT_HPP

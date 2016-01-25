#include "mml_object.hpp"
#include "mml_attribute.hpp"
#include "mml_manager.hpp"
#include "mml_registery.hpp"

#include <algorithm>
#include <cassert>

namespace MML
{

MMLObject::
MMLObject(const std::string& n, MMLObject* p)
    : m_parent(0)
{
    MMLAttribute* name = new MMLAttribute("name", n);
    addAttribute(name);
    setParent(p);
    MMLManager* m = MMLManager::getInstance();
    assert(0 != m);
    MMLRegistery* r = m->getRegistery();
    r->addObject(this);
}

MMLObject::
~MMLObject()
{
    std::for_each(m_children.begin(), m_children.end(),
                  [](MMLObject* o) { assert(o != 0); delete o;});
    m_children.clear();
    MMLManager* m = MMLManager::getInstance();
    assert(0 != m);
    MMLRegistery* r = m->getRegistery();
    r->removeObject(this);
}

std::string MMLObject::
getName() const
{
    const MMLAttribute* name = getAttribute("name");
    assert(0 != name);
    return name->getValue<std::string>();
}

MMLObject::CMMLAttributes& MMLObject::
getAttributes() const
{
    return m_attributes;
}

MMLAttribute* MMLObject::
getAttribute(const std::string& n)
{
    assert(!n.empty());
    MMLAttributes::iterator i =
                std::find_if(m_attributes.begin(), m_attributes.end(),
                [&](MMLAttribute* a)
                {
                    assert(0 != a);
                    return a->getName() == n;
                });
    return (i != m_attributes.end()) ? (*i): 0;
}

const MMLAttribute* MMLObject::
getAttribute(const std::string& n) const
{
    assert(!n.empty());
    MMLAttributes::const_iterator i =
                std::find_if(m_attributes.begin(), m_attributes.end(),
                [&](MMLAttribute* a)
                {
                    assert(0 != a);
                    return a->getName() == n;
                });
    return (i != m_attributes.end()) ? (*i): 0;
}

void MMLObject::
addAttribute(MMLAttribute* a)
{
    assert(0 != a);
    a->setParent(this);
    m_attributes.push_back(a);
}

const std::string& MMLObject::
getType()
{
    return m_type;
}

void MMLObject::
setType(const std::string& type)
{
    assert(!type.empty());
    m_type = type;
}

void MMLObject::
setParent(MMLObject* p)
{
    if (m_parent != 0) {
        m_parent->removeChild(this);
    }
    m_parent = p;
    p->addChild(this);
}

const MMLObject* MMLObject::
getParent() const
{
    return m_parent;
}

void MMLObject::
addChild(MMLObject* o)
{
    assert(0 != o);
    assert(o != this);
    Children::iterator i = std::find(m_children.begin(), m_children.end(), o);
    assert(i == m_children.end());
    m_children.push_back(o);
}

void MMLObject::
removeChild(MMLObject* o)
{
    assert(0 != o);
    assert(o != this);
    Children::iterator i = std::find(m_children.begin(), m_children.end(), o);
    assert(i != m_children.end());
    m_children.erase(i);
}

} // namespace MML

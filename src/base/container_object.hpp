#ifndef _BASE_CONTAINER_OBJECT_HPP_
#define _BASE_CONTAINER_OBJECT_HPP_

#include "object.hpp"

#include <algorithm>
#include <cassert>
#include <vector>

namespace Base
{

template <typename C>
class ContainerObject : public virtual Object
{
private:
    typedef std::vector<C*> Children;
    Children m_children;

protected:
    virtual void onObjectAdding(const C*) {}
    virtual void onObjectRemoving(const C*) {}

public:
    bool addObject(C* o)
    {
        assert(0 != o);
        typename Children::iterator i = std::find(m_children.begin(), m_children.end(), o);
        if (i != m_children.end()) {
            return false;
        }
        o->setParent(this);
        m_children.push_back(o);
        onObjectAdding(o);
        return true;
    }

    bool removeObject(const C* o)
    {
        assert(0 != o);
        assert(o->parent() == this);
        typename Children::iterator i =
                std::find(m_children.begin(), m_children.end(), o);
        if (m_children.end() == i) {
                return false;
        }
        onObjectRemoving(o);
        m_children.erase(i);
        return true;
    }

protected:
    Children& children()
    {
        return m_children;
    }

    const Children& childrenConst() const
    {
        return m_children;
    }

protected:
    /**
     * @brief This function sould be implemented in child objects
     */
    virtual void initObject()
    {}
    virtual void initObjectPost()
    {}

public:
    virtual void init()
    {
        initObject();
        std::for_each(m_children.begin(), m_children.end(), [](C* c) {
            assert(0 != c);
            c->init();
        });
        initObjectPost();
    }

public:
    ContainerObject()
        : Object()
        , m_children()
    {
    }
    virtual ~ContainerObject() = 0;
};

template<typename C>
ContainerObject<C>::~ContainerObject()
{
    std::for_each(m_children.begin(), m_children.end(), [](C* c) {
            assert(0 != c);
            delete c;
            });
    m_children.clear();
    assert(m_children.empty());
}

} // namespace Base

#endif // _BASE_CONTAINER_OBJECT_HPP_

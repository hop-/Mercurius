#ifndef _MML_MMLREGISTERY_HPP
#define _MML_MMLREGISTERY_HPP

#include "mml_object.hpp"

#include <algorithm>
#include <set>
#include <cassert>

namespace MML
{

class MMLRegistery
{
    struct less
    {
        bool operator()(MMLObject* a, MMLObject* b)
        {
            assert(0 != a);
            assert(0 != b);
            return a->getName() < b->getName();
        }
    };

    typedef std::set<MMLObject*, less> Objects;
    Objects m_objects = Objects();

public:
    typedef Objects::iterator iterator;

public:
    /**
     * @brief Adding MML object to registery
     * @param o pointer to MML object
     * @pre o != 0
     */
    bool addObject(MMLObject* o)
    {
        assert(0 != o);
        return m_objects.insert(o).second;
    }

public:
    bool removeObject(MMLObject* o)
    {
        assert(0 != o);
        return m_objects.erase(o);
    }

public:
    iterator begin()
    {
        return m_objects.begin();
    }

public:
    iterator end()
    {
        return m_objects.end();
    }

public:
    /**
     * @brief Return MML objects of coresponding type
     * @param v container in which objects will be added
     * @pre v.empty() == true
     */
    template <typename T>
    void getObjects(std::vector<T*>& v)
    {
        assert(v.empty());
        for (iterator i = begin(); i != end(); ++i) {
            assert(*i != 0);
            T* obj = dynamic_cast<T*>(*i);
            if (obj != 0) {
                v.push_back(obj);
            }
        }
    }

public:
    ~MMLRegistery()
    {
        m_objects.clear();
        assert(m_objects.empty());
    }
};

} // namespace MML

#endif // _MML_MMLREGISTERY_HPP

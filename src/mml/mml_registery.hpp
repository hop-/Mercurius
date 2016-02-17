#ifndef _MML_MMLREGISTERY_HPP
#define _MML_MMLREGISTERY_HPP

#include "mml_object.hpp"

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

    Objects m_objects;

public:
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
};

} // namespace MML

#endif // _MML_MMLREGISTERY_HPP

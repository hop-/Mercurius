#ifndef _CORE_QUAD_TREE_HPP_
#define _CORE_QUAD_TREE_HPP_

#include "rectangle.hpp"

#include <list>
#include <vector>

namespace Core
{

class Collider;

class QuadTree
{
public:
    using Objects = std::list<const Collider*>;

private:
    static const int m_maxObjects;
    static const int m_maxLevel;

    const int m_level;
    Objects m_objects;
    Rectangle m_bounds;
    std::vector<QuadTree> m_nodes;

public:
    QuadTree(int level, Rectangle bound);
    void clear();
    void insert(const Collider* c);
    void remove(const Collider* c);
//    bool update(const Collider* c, const Rectangle& newRect);
    Objects retreive(const Collider* c);
    Objects retreive(const Rectangle& r);
    void setBounds(Rectangle bounds);

private:
    void split();
    int getIndex(Rectangle rect);
};

} // namespace Core

#endif //_CORE_QUAD_TREE_HPP_

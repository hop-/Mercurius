#include "quad_tree.hpp"

#include "components.hpp"
#include "units.hpp"

namespace Core
{
const int QuadTree::m_maxObjects = 10;
const int QuadTree::m_maxLevel = 5;

QuadTree::QuadTree(int level, Rectangle bound)
    : m_level(level)
    , m_objects()
    , m_bounds(bound)
    , m_nodes()
{}

void QuadTree::clear()
{
    m_objects.clear();
    for (auto& node : m_nodes) {
        node.clear();
    }
}

void QuadTree::split()
{
    EngineUnit w = m_bounds.width() / 2;
    EngineUnit h = m_bounds.height() / 2;
    EngineUnit x0 = m_bounds.position().x();
    EngineUnit y0 = m_bounds.position().y();
    EngineUnit x1 = m_bounds.position().x() + w;
    EngineUnit y1 = m_bounds.position().y() + h;
    m_nodes.push_back(QuadTree(m_level + 1
            , Rectangle(w, h, Position(x1, y0))));
    m_nodes.push_back(QuadTree(m_level + 1
            , Rectangle(w, h, Position(x0, y0))));
    m_nodes.push_back(QuadTree(m_level + 1
            , Rectangle(w, h, Position(x0, y1))));
    m_nodes.push_back(QuadTree(m_level + 1
            , Rectangle(w, h, Position(x1, y1))));
}

int QuadTree::getIndex(Rectangle rect)
{
    int index = -1;
    if (m_nodes.size() == 0) {
        return index;
    }
    double verticalMidpoint = m_bounds.position().x()
        + (m_bounds.width() / 2);
    double horizontalMidpoint = m_bounds.position().y()
        + (m_bounds.height() / 2);
    bool topQuadrant = (rect.position().y() < horizontalMidpoint
            && rect.position().y() + rect.height() < horizontalMidpoint);
    bool bottomQuadrant = (rect.position().y() > horizontalMidpoint);
    if (rect.position().x() < verticalMidpoint
            && rect.position().x() + rect.width() < verticalMidpoint) {
        if (topQuadrant) {
            index = 1;
        } else if (bottomQuadrant) {
            index = 2;
        }
    } else if (rect.position().x() > verticalMidpoint) {
        if (topQuadrant) {
            index = 0;
        } else if (bottomQuadrant) {
            index = 3;
        }
    }
    return index;
}

void QuadTree::insert(const Collider* c)
{
    int index = getIndex(c->rect());
    if (index != -1) {
        m_nodes[index].insert(c);
        return;
    }
    m_objects.push_back(c);
    if (m_objects.size() > m_maxObjects && m_level < m_maxLevel) {
        if (m_nodes.size() == 0) {
            split();
        }
        Objects::iterator it = m_objects.begin();
        while (it != m_objects.end()) {
            int index = getIndex((*it)->rect());
            if (index != -1) {
                m_nodes[index].insert(*it);
                m_objects.erase(it);
            } else {
                ++it;
            }
        }
    }
}

void QuadTree::remove(const Collider* c)
{
    int index = getIndex(c->rect());
    if (index != -1) {
        m_nodes[index].remove(c);
        return;
    }
    // TODO performance improvement
    for (Objects::iterator it = m_objects.begin()
            ; it != m_objects.end();
            ++it) {
        if (c->parent() == (*it)->parent()) {
            m_objects.erase(it);
            break;
        }
    }
}

/* TODO
bool QuadTree::update(const Collider* c, const Rectangle& newRect)
{
    bool returnFlag = false;
    int index = getIndex(c->ect);
    if (index != -1) {
        returnFlag = m_nodes[index].update(c, newRect);
    }
    if (!returnFlag) {
        if (m_bounds.isInside(newRect)) {
            remove(c);
            insert(c, newRect);
            returnFlag = true;
        }
    }
    return returnFlag;
}
*/

QuadTree::Objects QuadTree::retreive(const Collider* c)
{
    return retreive(c->rect());
}

QuadTree::Objects QuadTree::retreive(const Rectangle& rect)
{
    Objects returnList;
    int index = getIndex(rect);
    if (index != -1) {
        Objects tmp = m_nodes[index].retreive(rect);
        returnList.insert(returnList.end(), tmp.begin(), tmp.end());
    }
    returnList.insert(returnList.end()
        , m_objects.begin()
        , m_objects.end());
    return returnList;
}

} // namespace Core

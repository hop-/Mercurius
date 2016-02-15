#ifndef _CORE_LOGIC_HPP_
#define _CORE_LOGIC_HPP_

#include <cassert>
#include <vector>

namespace Core
{

class Layer;
class LogicObject;

class Logic
{
public:
    typedef std::vector<LogicObject*> LogicObjects;

private:
    LogicObjects m_objects;
    Layer* m_parent;

public:
    void addLogicObject(LogicObject* o);
    void removeLogicObject(LogicObject* o);

public:
    inline Layer* parent() const
    {
        return m_parent;
    }

    inline const LogicObjects& objects() const
    {
        return m_objects;
    }

    inline void setParent(Layer* parent)
    {
        assert(0 != parent);
        m_parent = parent;
    }

public:
    virtual ~Logic();
    virtual void update();
};

} // namespace Core

#endif //_CORE_LOGIC_HPP_

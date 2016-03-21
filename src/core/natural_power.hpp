#ifndef _CORE_NATURAL_POWER_HPP_
#define _CORE_NATURAL_POWER_HPP_

#include "logic_object.hpp"

namespace Core
{

class NaturalPower : public Base::Object
{
public:
    NaturalPower()
        : Base::Object()
        , m_factory(0)
    {}

public:
    virtual ~NaturalPower()
    {
        if (m_factory != 0) {
            delete m_factory;
            m_factory = 0;
        }
    }

public:
    /**
     * @brief Interface for adding coresponding component to give logic object
     * @param l, pointe to logic object
     * @pre l should be valid pointer
     */
    void addComponentToObject(LogicObject* l)
    {
        assert(0 != l);
        assert(0 != m_factory);
        l->addComponent(m_factory->createComponent());
    }

protected:
    class ComponentAbstractFactory
    {
    public:
        virtual ~ComponentAbstractFactory()
        {}

    public:
        virtual LogicObject::Component* createComponent() = 0;
    };

    void setComponentCreator(ComponentAbstractFactory* f)
    {
        assert(0 != f);
        assert(0 == m_factory);
        m_factory = f;
    }

private:
    ComponentAbstractFactory* m_factory;
};

} // end of namespace Core

#endif // _CORE_NATURAL_POWER_HPP_

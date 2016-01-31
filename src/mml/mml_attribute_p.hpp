#ifndef _MML_MMLATTRIBUTE_PRIVATE_HPP
#define _MML_MMLATTRIBUTE_PRIVATE_HPP

#include <cassert>
#include <string>

namespace MML
{

class MMLAttribute;

class MMLAttributePrivate
{
public:
    class AttrHolder
    {
    public:
        enum Type {string_t = 0, int_t, double_t, bool_t};

    public:
        AttrHolder(const std::string& v)
            : m_string(v)
            , m_int(0)
            , m_double(0)
            , m_bool(false)
            , m_type(string_t)
        {
        }

    public:
        AttrHolder(int v)
            : m_string("")
            , m_int(v)
            , m_double(0)
            , m_bool(false)
            , m_type(int_t)
        {
        }

    public:
        AttrHolder(double v)
            : m_string("")
            , m_int(0)
            , m_double(v)
            , m_bool(false)
            , m_type(double_t)
        {
        }
    
    public:
        AttrHolder(bool v)
            : m_string("")
            , m_int(0)
            , m_double(0)
            , m_bool(v)
            , m_type(bool_t)
        {
        }

    public:
        AttrHolder(const AttrHolder& a)
        {
            m_string = a.m_string;
            m_int = a.m_int;
            m_double = a.m_double;
            m_type = a.m_type;
        }
    
    public:
        AttrHolder& operator=(const AttrHolder& a)
        {
            if (this == &a) {
                return *this;
            }
            m_string = a.m_string;
            m_int = a.m_int;
            m_double = a.m_double;
            m_bool = a.m_bool;
            m_type = a.m_type;
            return *this;
        }
    public:
        operator int () const
        {
            return m_int;
        }

        operator double () const
        {
            return m_double;
        }
        
        operator std::string () const
        {
            return m_string;
        }
    
        operator bool () const
        {
            return m_bool;
        }

    public:
        Type getType() const
        {
            return m_type;
        }        
 
    private:
        std::string m_string;
        int m_int;
        double m_double;
        bool m_bool;
        Type m_type;
    };

    typedef AttrHolder ValueType;

public:
    MMLAttributePrivate(const ValueType& v, MMLAttribute* parent)
        : m_parent(parent)
        , m_value(v)
    {
        assert(parent != 0);
    }

public:
    MMLAttributePrivate(const MMLAttributePrivate& a, MMLAttribute* parent)
        : m_parent(parent)
        , m_value(a.m_value)
    {
    }

public:
    const ValueType& getValue() const
    {
        return m_value;
    }

    void setValue(const ValueType& v)
    {
        m_value = v;
    }

public:
    AttrHolder::Type getType() const
    {
        return m_value.getType();
    }

protected:
    MMLAttribute* getParent()
    {
        return m_parent;
    }

private:
    MMLAttribute* m_parent;
    ValueType m_value;
};

} // MML

#endif // _MML_MMLATTRIBUTE_HPP

#ifndef _MML_MMLATTRIBUTE_PRIVATE_HPP
#define _MML_MMLATTRIBUTE_PRIVATE_HPP

#include <core/frame.hpp>

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
        enum Type {
            string_t = 0,
            int_t,
            double_t,
            bool_t,
            int_pair_t,
            screen_mode_t,
            pair_t
        };

    public:
        typedef std::pair<int, int> IntPair;
        typedef std::pair<float, float> Pair;
        typedef Core::Frame::ScreenMode ScreenMode;

    public:
        AttrHolder(const std::string& v)
            : m_string(v)
            , m_type(string_t)
        {
        }

    public:
        AttrHolder(int v)
            : m_int(v)
            , m_type(int_t)
        {
        }

    public:
        AttrHolder(double v)
            : m_double(v)
            , m_type(double_t)
        {
        }

    public:
        AttrHolder(bool v)
            : m_bool(v)
            , m_type(bool_t)
        {
        }

    public:
        AttrHolder(IntPair v)
            : m_intPair(v)
            , m_type(int_pair_t)
        {
        }

    public:
        AttrHolder(Pair v)
            : m_pair(v)
            , m_type(pair_t)
        {
        }

    public:
        AttrHolder(ScreenMode v)
            : m_screenMode(v)
            , m_type(screen_mode_t)
        {
        }

    public:
        AttrHolder(const AttrHolder& a)
            : m_string(a.m_string)
            , m_int(a.m_int)
            , m_double(a.m_double)
            , m_bool(a.m_bool)
            , m_intPair(a.m_intPair)
            , m_pair(a.m_pair)
            , m_screenMode(a.m_screenMode)
            , m_type(a.m_type)
        {
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
            m_intPair = a.m_intPair;
            m_pair = a.m_pair;
            m_screenMode = a.m_screenMode;
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

        operator IntPair() const
        {
            return m_intPair;
        }

        operator Pair() const
        {
            return m_pair;
        }

        operator ScreenMode() const
        {
            return m_screenMode;
        }

    public:
        Type getType() const
        {
            return m_type;
        }

    private:
        std::string m_string = "";
        int m_int = 0;
        double m_double = 0;
        bool m_bool = false;
        IntPair m_intPair = IntPair(0, 0);
        Pair m_pair = Pair(0.0f, 0.0f);
        ScreenMode m_screenMode = ScreenMode::fullScreenFit;
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

private:
    MMLAttributePrivate(const MMLAttributePrivate&) = delete;
    MMLAttributePrivate& operator=(const MMLAttributePrivate&) = delete;

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

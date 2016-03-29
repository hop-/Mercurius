#ifndef _BASE_OBJECT_HPP_
#define _BASE_OBJECT_HPP_

#include <cassert>
#include <string>

namespace Base
{

class Object
{
public:
    Object();
    virtual ~Object();

private:
    // TMP
    Object(const Object&) = delete;
    Object& operator=(const Object&) = delete;

public:
    virtual void init() = 0;

public:
    Object* parent() const;

public:
    template <typename R>
    R* parent() const
    {
        assert(0 != m_parent);
        return dynamic_cast<R*>(m_parent);
    }

public:
    void setParent(Object* p);

public:
    const std::string& name() const;

protected:
    void setName(const std::string&);

private:
    std::string m_name;
    Object* m_parent;
};

} // namespace Base

#endif // _BASE_OBJECT_HPP_

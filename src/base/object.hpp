#ifndef _BASE_OBJECT_HPP_
#define _BASE_OBJECT_HPP_

#include <string>

namespace Base
{

class Object
{
public:
    Object();
    virtual ~Object();    

public:
    virtual void init() = 0;

public:
    Object* parent();

public:
    template <typename R>
    R* parent()
    {
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

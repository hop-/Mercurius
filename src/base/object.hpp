#ifndef _BASE_OBJECT_HPP_
#define _BASE_OBJECT_HPP_

#include "callback.hpp"

#include <cassert>
#include <string>
#include <vector>

namespace Base
{

class Object
{
public:
    Object();
    virtual ~Object();

private:
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
    void deleteLater();

public:
    const std::string& name() const;

protected:
    void setName(const std::string&);
    void deactivateCallbacks();

    template <class T>
    void registerCallback(Delegate* d)
    {
        m_callbacks.push_back(new CallbackCreator<T>(this, d));
    }

private:
    using Callbacks = std::vector<Callback*>;

    Callbacks m_callbacks;
    std::string m_name;
    Object* m_parent;
};

} // namespace Base

#endif // _BASE_OBJECT_HPP_

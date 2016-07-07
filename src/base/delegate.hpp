#ifndef _BASE_DELEGATE_HPP_
#define _BASE_DELEGATE_HPP_

#include <functional>
#include <cassert>

namespace Base
{

class Event;

class Delegate
{
    bool m_isNotActive = false;

public:
    virtual void invoke(Event*) = 0;
    virtual ~Delegate() = default;
    void activate();
    void deactivate();

protected:
    bool isNotActive() const;
};

template <class T>
class DelegateCreator : public Delegate
{
public:
    using Function = std::function<void (T*, Event*)>;

private:
    T* m_object;
    Function m_function;

public:
    DelegateCreator(T* obj, Function fn)
        : m_object(obj)
        , m_function(fn)
    {
        assert(0 != obj);
    }

    ~DelegateCreator() = default;

public:
    void invoke(Event* e) override final
    {
        assert(0 != m_object);
        if (isNotActive()) {
            return;
        }
        m_function(m_object, e);
    }

private:
    DelegateCreator(const DelegateCreator&) = delete;
    DelegateCreator& operator=(const DelegateCreator&) = delete;
};

} // end of namespace Base

#endif // _BASE_DELEGATE_HPP_

#ifndef _ASSETS_EVENTS_HPP_
#define _ASSETS_EVENTS_HPP_

#include <core/event.hpp>

namespace Core
{
class LogicObject;
}

namespace Assets
{

class OnSurface
    : public Core::EventCreator<OnSurface>
{
    const Core::LogicObject* m_object;

public:
    OnSurface(const Core::LogicObject* object);

    inline const Core::LogicObject* object() const
    {
        return m_object;
    }

private:
    OnSurface(const OnSurface&) = delete;
    OnSurface& operator=(const OnSurface&) = delete;

    bool less(Base::TypedBase* obj) override;
};

class OnAir
    : public Core::EventCreator<OnAir>
{
    const Core::LogicObject* m_object;

public:
    OnAir(const Core::LogicObject* object);

    inline const Core::LogicObject* object() const
    {
        return m_object;
    }

private:
    OnAir(const OnAir&) = delete;
    OnAir& operator=(const OnAir&) = delete;

    bool less(Base::TypedBase* obj) override;
};

} // namespace Assets

#endif //_ASSETS_EVENTS_HPP_

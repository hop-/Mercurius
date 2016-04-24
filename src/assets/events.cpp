#include "events.hpp"

namespace Assets
{

OnSurface::OnSurface(Core::LogicObject* object)
    : m_object(object)
{}

bool OnSurface::less(Base::TypedBase* obj)
{
    return (this < obj);
}

OnAir::OnAir(Core::LogicObject* object)
    : m_object(object)
{}

bool OnAir::less(Base::TypedBase* obj)
{
    return (this < obj);
}

} // namespace Assets

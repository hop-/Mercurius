#ifndef _BASE_DELETE_EVENT_HPP_
#define _BASE_DELETE_EVENT_HPP_

#include "event.hpp"

namespace Base
{

class Object;

class DeleteEvent
    : public EventCreator<DeleteEvent>
{
private:
    Object* m_object;

public:
    DeleteEvent(Object* o);
    virtual ~DeleteEvent();

public:
    void trigger() override final;

private:
    DeleteEvent(const DeleteEvent&) = delete;
    DeleteEvent& operator=(const DeleteEvent&) = delete;
};

} // end of namespace Base

#endif // _BASE_DELETE_EVENT_HPP_

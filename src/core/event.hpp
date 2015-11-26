#ifndef _EVENT_HPP_
#define _EVENT_HPP_

#include <cassert>

namespace Core
{

class Event
{
public:
    class ID
    {
        static int m_count;
        const int m_id;

     public:
        ID();
        operator int() const;
    };

    struct Less
    {
        bool operator() (Event* lEvent, Event* rEvent)
        {
            assert(0 != lEvent);
            assert(0 != rEvent);
            if (lEvent->getType() == rEvent->getType()) {
                return lEvent->less(rEvent);
            }
            return lEvent->getType() < rEvent->getType();
        }
        typedef Event* first_argument_type;
        typedef Event* second_argument_type;
        typedef bool result_type;
    };

    virtual ~Event() = default;
    virtual int getType() const = 0;

private:
    virtual bool less(Event* event) = 0;
};

template <class T>
class EventCreator :
    public Event
{
    static const ID type;

public:
    int getType() const
    {
        return type;
    }
};

template<class T>
const Event::ID EventCreator<T>::type;

} // namespace Core

#endif //_EVENT_HPP_

#ifndef _EVENT_HPP_
#define _EVENT_HPP_

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

public:
    virtual ~Event() = default;
    virtual int getType() const = 0;
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

#ifndef _DEBUG_LOG_HPP_
#define _DEBUG_LOG_HPP_

#include <core/position.hpp>
#include <core/rectangle.hpp>

#include <iostream>

namespace Debug
{

class Log
{

// use static functions to implement logging mechanism
#ifdef DM_NO_DEBUG
public:
    template <class T>
    static void print(T) {}

    template <class T>
    static void print(std::string, T) {}
#else
public:
    template <class T>
    static void print(const T& t)
    {
        std::cout << t << std::endl;
    }

    static void print(const Core::Position& p)
    {
        std::cout << p.x() << ", " << p.y() << std::endl;
    }

    static void print(const Core::Rectangle& r)
    {
        std::cout << "(" << r.position().x()
            << ", " << r.position().y()
            << "), " << r.width()
            << ", " << r.height() << std::endl;
    }

    template <class T>
    static void print(std::string s, const T& t)
    {
        std::cout << s << " ";
        print(t);
    }
#endif // DM_NO_DEBUG

};

} // namespace Debug

#endif //_DEBUG_LOG_HPP_

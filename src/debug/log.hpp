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
#ifdef M_NO_DEBUG
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

    static void print(const Core::Direction& d)
    {
        std::cout << "Direction ";
        switch (d) {
            case Core::Direction::Left:
                std::cout << "Left";
                break;
            case Core::Direction::Right:
                std::cout << "Right";
                break;
            case Core::Direction::Up:
                std::cout << "Up";
                break;
            case Core::Direction::Down:
                std::cout << "Down";
                break;
            case Core::Direction::None:
                std::cout << "None";
                break;
        }
        std::cout << std::endl;
    }

    static void print(const Core::HorizontalDirection& d)
    {
        std::cout << "HorizontalDirection ";
        switch (d) {
            case Core::HorizontalDirection::Left:
                std::cout << "Left";
                break;
            case Core::HorizontalDirection::Right:
                std::cout << "Right";
                break;
            case Core::HorizontalDirection::None:
                std::cout << "None";
                break;
        }
        std::cout << std::endl;
    }

    static void print(const Core::VerticalDirection& d)
    {
        std::cout << "VerticalDirection ";
        switch (d) {
            case Core::VerticalDirection::Up:
                std::cout << "Up";
                break;
            case Core::VerticalDirection::Down:
                std::cout << "Down";
                break;
            case Core::VerticalDirection::None:
                std::cout << "None";
                break;
        }
        std::cout << std::endl;
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

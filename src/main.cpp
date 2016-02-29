// main.cpp

#include <base/exception.hpp>
#include <sdl/mercurius.hpp>

#include <iostream>

int main(int argc, char** argv)
{   
    try {
        Sdl::Mercurius::start();
    } catch (const Base::Exception& e) {
        std::cerr<<e.what()<<std::endl;
    }
    return 0;
}

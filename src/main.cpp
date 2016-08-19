// main.cpp

#include <base/exception.hpp>
#include <base/utility.hpp>
#include <assets/mercurius.hpp>

#include <iostream>

int main(int argc, char** argv)
{
    try {
        Assets::Mercurius m;
        m.play();
    } catch (const Base::Exception& e) {
        std::cerr<<e.what()<<std::endl;
    }
    Base::Utility::ignoreUnused(argc, argv);
    return 0;
}

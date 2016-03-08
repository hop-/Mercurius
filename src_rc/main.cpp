#include <core/resource_converter.hpp>
//#include <core/options.hpp>

#include <iostream>
#include <string>

int main(int argc, char* argv[])
{
    //Core::Options opts(argc, argv);
    // TMP begin
    std::string exec = argv[0];
    if (argc != 2) {
        std::cerr << "Usage:\n\t"
            << exec
            << " <resource root directory>\n"
            << std::endl;
        return 1;
    }
    std::string resourceRoot = argv[1];
    // TMP end
    Core::ResourceConverter res(resourceRoot);
    return 0;
}

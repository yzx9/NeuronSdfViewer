#include <iostream>
#include "Viewer.hpp"

int main()
{
    try {
        Viewer app{};
        app.run();
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

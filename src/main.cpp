#include <exception>
#include <iostream>
#include "neuron/NeuronViewer.hpp"
#include "utils/debug.hpp"

int main()
{
    try
    {
        NeuronViewer viewer;
        viewer.load("../assets/228-1-NBSS.CNG.swc");

        run_with_duration("Build BVH", [&]
                          { viewer.build_bvh(); });
        run_with_duration("Render", [&]
                          { viewer.render_image(); });

        viewer.show_image();
        return EXIT_SUCCESS;
    }
    catch (std::exception &ex)
    {
        std::cerr << ex.what() << std::endl;
        return EXIT_FAILURE;
    }
}

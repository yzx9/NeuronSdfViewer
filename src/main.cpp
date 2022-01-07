#include <stdexcept>
#include <stdlib.h>
#include <iostream>
#include <opencv2/opencv.hpp>

import Neuron;
import Utils.Debug;

int main()
{
    try
    {
        NeuronViewer viewer;
        viewer.load("../assets/228-1-NBSS.CNG.swc");

        runWithClockInfo("Build BVH", [&] { viewer.build_bvh(); });
        runWithClockInfo("Render", [&] { viewer.render_image(); });

        viewer.show_image();
        cv::waitKey(0);
        return EXIT_SUCCESS;
    }
    catch (std::exception &ex)
    {
        std::cerr << ex.what() << std::endl;
        return EXIT_FAILURE;
    }
}

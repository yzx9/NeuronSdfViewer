#include <chrono>
#include <string>
#include <stdlib.h>
#include <iostream>
#include <exception>
#include <functional>
#include <opencv2/opencv.hpp>
#include "neuron/NeuronViewer.hpp"

void runWithClockInfo(const std::string& title, std::function<void()> task);

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

void runWithClockInfo(const std::string &title, std::function<void()> task)
{
    auto start = std::chrono::steady_clock::now();
    task();
    auto stop = std::chrono::steady_clock::now();
    auto nanoseconds = stop - start;

    auto hours = std::chrono::duration_cast<std::chrono::hours>(nanoseconds);
    nanoseconds -= hours;

    auto minutes = std::chrono::duration_cast<std::chrono::minutes>(nanoseconds);
    nanoseconds -= minutes;

    auto seconds = std::chrono::duration_cast<std::chrono::seconds>(nanoseconds);
    nanoseconds -= seconds;

    auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(nanoseconds);

    std::cout << title << " complete: " << std::endl
              << "Time taken: " << std::setw(4) << hours.count() << " hours, " << std::endl
              << "            " << std::setw(4) << minutes.count() << " minutes, " << std::endl
              << "            " << std::setw(4) << seconds.count() << " seconds, " << std::endl
              << "            " << std::setw(4) << milliseconds.count() << " milliseconds." << std::endl
              << std::endl;
}

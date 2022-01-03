#include <chrono>
#include <stdlib.h>
#include <iostream>
#include <exception>
#include <Eigen/Dense>
#include <opencv2/opencv.hpp>
#include "render/Render.hpp"
#include "render/camera/OrthographicCamera.hpp"
#include "neuron/NeuronScene.hpp"

constexpr auto title = "neuron-sdf-viewer";
constexpr auto width = 620;
constexpr auto height = 480;

constexpr auto model = "../assets/228-1-NBSS.CNG.swc";

void renderImage();
void printClockInfo(std::chrono::nanoseconds nanoseconds) noexcept;

int main()
{
    try
    {
        auto start = std::chrono::steady_clock::now();
        renderImage();
        auto stop = std::chrono::steady_clock::now();

        printClockInfo(stop - start);
        cv::waitKey(0);
        return EXIT_SUCCESS;
    }
    catch (std::exception &ex)
    {
        std::cerr << ex.what() << std::endl;
        return EXIT_FAILURE;
    }
}

void renderImage()
{
    NeuronScene scene;
    scene.load(model);

    OrthographicCamera camera(-width / 2, width / 2, height / 2, -height / 2, 0.5, 2000);

    Render render(width, height);
    render.draw(scene, camera);

    auto &colorBuffer = render.get_frame_buffer();
    cv::Mat img(height, width, CV_8UC3, colorBuffer.data());
    cv::imshow(title, img);
}

void printClockInfo(std::chrono::nanoseconds nanoseconds) noexcept
{
    auto hours = std::chrono::duration_cast<std::chrono::hours>(nanoseconds);
    nanoseconds -= hours;

    auto minutes = std::chrono::duration_cast<std::chrono::minutes>(nanoseconds);
    nanoseconds -= minutes;

    auto seconds = std::chrono::duration_cast<std::chrono::seconds>(nanoseconds);
    nanoseconds -= seconds;

    auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(nanoseconds);

    std::cout << "Render complete: " << std::endl
              << "Time taken: " << std::setw(4) << hours.count() << " hours, " << std::endl
              << "            " << std::setw(4) << minutes.count() << " minutes, " << std::endl
              << "            " << std::setw(4) << seconds.count() << " seconds, " << std::endl
              << "            " << std::setw(4) << milliseconds.count() << " milliseconds." << std::endl;
}

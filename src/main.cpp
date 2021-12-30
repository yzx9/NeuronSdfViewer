#include <stdlib.h>
#include <iostream>
#include <Eigen/Dense>
#include <opencv2/opencv.hpp>
#include "render/Render.hpp"
#include "neuron/NeuronScene.hpp"

constexpr auto title = "neuron-sdf-viewer";
constexpr auto width = 620;
constexpr auto height = 480;

int main()
{
    NeuronScene scene;
    scene.load("");

    Render render(width, height);
    render.draw(scene);
    auto& colorBuffer = render.get_frame_buffer();

    cv::Mat img(height, width, CV_8UC3, colorBuffer.data());
    cv::imshow(title, img);
    cv::waitKey(0);

    return EXIT_SUCCESS;
}

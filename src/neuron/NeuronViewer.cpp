#include <string>
#include <opencv2/opencv.hpp>
#include "NeuronViewer.hpp"

NeuronViewer::NeuronViewer(std::string model)
    : scene(), render(width, height), camera(-width / 2, width / 2, height / 2, -height / 2, 0.5, 2000)
{
    scene.load(model);
}

void NeuronViewer::build_bvh()
{
    scene.build_bvh();
}

void NeuronViewer::render_image()
{
    render.draw(scene, camera);
}

void NeuronViewer::show_image()
{
    auto& colorBuffer = render.get_frame_buffer();
    cv::Mat img(height, width, CV_8UC3, colorBuffer.data());
    cv::imshow(title, img);
}
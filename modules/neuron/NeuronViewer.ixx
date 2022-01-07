module;
#include <string>
#include <Eigen/Dense>
#include <opencv2/opencv.hpp>
export module Neuron.Viewer;

import Neuron.Scene;
import Render;
import Render.Camera;

constexpr auto title = "neuron-sdf-viewer";
constexpr auto width = 620;
constexpr auto height = 480;

export class NeuronViewer
{
public:
    NeuronViewer();
    void load(std::string model);
    void build_bvh();
    void render_image();
    void show_image();

private:
    NeuronScene scene;
    OrthographicCamera camera;
    Render render;
};

NeuronViewer::NeuronViewer()
    : scene(), render(width, height), camera(-width / 2, width / 2, height / 2, -height / 2, 0.5, 2000)
{
}

void NeuronViewer::load(std::string model)
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

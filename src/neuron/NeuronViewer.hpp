#pragma once
#include <Eigen/Dense>
#include <string>
#include "NeuronScene.hpp"
#include "../render/Render.hpp"
#include "../render/camera/OrthographicCamera.hpp"

constexpr auto title = "neuron-sdf-viewer";
constexpr auto width = 620;
constexpr auto height = 480;

class NeuronViewer
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

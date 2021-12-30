#pragma once

#include <vector>
#include <Eigen/Dense>
#include "Scene.hpp"

using ColorBuffer = std::vector<Eigen::Matrix<uint8_t, 3, 1>>;

class Render
{
public:
    Render(int width, int height);
    void draw(const Scene &scene);
    ColorBuffer& get_frame_buffer();

private:
    int width;
    int height;
    int size;

    ColorBuffer color_buffer;
};

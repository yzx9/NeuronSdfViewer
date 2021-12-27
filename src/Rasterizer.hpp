#pragma once

#include <vector>
#include "Scene.hpp"

class Rasterizer
{
public:
    void draw(const Scene &scene);
    std::vector<Eigen::Vector3f> get_frame_buffer();

private:
    std::vector<Eigen::Vector3f> frame_buffer;
};

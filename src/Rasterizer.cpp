#include "Rasterizer.hpp"

void Rasterizer::draw(const Scene &scene)
{
    auto size = scene.width * scene.height;
    frame_buffer.resize(size);
    for (auto i = 0; i < scene.height; i++) {
        for (auto j = 0; j < scene.width; j++) {
            auto m = i * scene.width + j;
            auto v = static_cast<float>(m) / size;
            frame_buffer[m] = { v, v, v };
        }
    }
}

std::vector<Eigen::Vector3f> Rasterizer::get_frame_buffer()
{
    return frame_buffer;
}
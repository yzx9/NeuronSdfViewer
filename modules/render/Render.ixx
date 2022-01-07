module;
#include <limits>
#include <vector>
#include <future>
#include <Eigen/Dense>
export module Render.Render;

import Render.Cameras.Camera;
import Render.Scene;

// TODO: Support custom type instead uint8_t
using ColorBuffer = std::vector<Eigen::Matrix<uint8_t, 3, 1>>;

class Render
{
public:
    Render(int width, int height);

    void draw(const Scene& scene, const Camera& camera);

    ColorBuffer& get_frame_buffer() noexcept;

private:
    int width;
    int height;
    int size;

    ColorBuffer color_buffer;
};


Render::Render(int width, int height)
    : width(width), height(height), size(width * height)
{
    color_buffer.resize(size);
}

void Render::draw(const Scene &scene, const Camera &camera)
{
    auto calcPixel = [&](auto offsetX, auto offsetY) {
        auto x = (static_cast<float>(offsetX) / width) * 2 - 1;
        auto y = (static_cast<float>(offsetY) / height) * 2 - 1;

        auto ray = camera.generate_primary_ray(x, y);
        auto color = scene.cast_ray(ray);

        constexpr auto max = std::numeric_limits<uint8_t>::max();
        return Eigen::Matrix<uint8_t, 3, 1> {
            static_cast<uint8_t>(max * color[0]),
            static_cast<uint8_t>(max * color[1]),
            static_cast<uint8_t>(max * color[2])
        };
    };

    std::vector<std::future<Eigen::Matrix<uint8_t, 3, 1>>> futures;
    futures.reserve(size);
    for (auto i = 0; i < height; i++) {
        for (auto j = 0; j < width; j++) {
            std::future<Eigen::Matrix<uint8_t, 3, 1>> fut = std::async(calcPixel, j, i);
            futures.emplace_back(std::move(fut));
        }
    }

    for (int m = 0; m < size; m++)
        color_buffer[m] = futures[m].get();
}

ColorBuffer& Render::get_frame_buffer() noexcept
{
    return color_buffer;
}
#pragma once
#include <limits>
#include <vector>
#include <future>
#include <Eigen/Dense>
#include "Scene.hpp"
#include "camera/Camera.hpp"

class Render
{
    // TODO: Support custom type instead uint8_t
    using ColorBuffer = std::vector<Eigen::Matrix<uint8_t, 3, 1>>;

private:
    int width;
    int height;
    int size;

    ColorBuffer color_buffer;

public:
    Render(int width, int height) : width(width), height(height), size(width * height)
    {
        color_buffer.resize(size);
    };

    void draw(const Scene &scene, const Camera &camera)
    {
        auto calcPixel = [&](auto offsetX, auto offsetY)
        {
            auto x = (static_cast<float>(offsetX) / width) * 2 - 1;
            auto y = (static_cast<float>(offsetY) / height) * 2 - 1;

            auto ray = camera.generate_primary_ray(x, y);
            auto color = scene.cast_ray(ray);

            constexpr auto cast = [](float color)
            {
                constexpr auto max = std::numeric_limits<uint8_t>::max();
                return static_cast<uint8_t>(max * color);
            };

            return Eigen::Vector3<uint8_t>{cast(color[0]), cast(color[1]), cast(color[2])};
        };

        std::vector<std::future<Eigen::Matrix<uint8_t, 3, 1>>> futures;
        futures.reserve(size);
        for (auto i = 0; i < height; i++)
            for (auto j = 0; j < width; j++)
                futures.emplace_back(std::async(calcPixel, j, i));

        for (int m = 0; m < size; m++)
        {
            futures[m].wait();
            // TODO: Progress
        }

        for (int m = 0; m < size; m++)
            color_buffer[m] = futures[m].get();
    };

    ColorBuffer &get_frame_buffer() noexcept { return color_buffer; };
};

#include <limits>
#include "Render.hpp"
#include "Scene.hpp"

Render::Render(int width, int height)
    : width(width), height(height), size(width * height)
{
    color_buffer.resize(size);
}

void Render::draw(const Scene &scene)
{
    for (auto i = 0; i < height; i++) {
        auto y = (static_cast<float>(i) / height) * 2 - 1;

        for (auto j = 0; j < width; j++) {
            auto x = (static_cast<float>(j) / width) * 2 - 1;

            Ray ray({ x, y, -1 }, { 0, 0, 1 });
            auto color = scene.cast_ray(ray);
            color_buffer[i * width + j] = {
                static_cast<uint8_t>(std::numeric_limits<uint8_t>::max() * color[0]),
                static_cast<uint8_t>(std::numeric_limits<uint8_t>::max() * color[1]),
                static_cast<uint8_t>(std::numeric_limits<uint8_t>::max() * color[2])
            };
        }
    }
}

ColorBuffer& Render::get_frame_buffer()
{
    return color_buffer;
}
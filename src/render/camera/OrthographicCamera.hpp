#pragma once
#include "Camera.hpp"
#include "../Ray.hpp"

class OrthographicCamera : public Camera
{
public:
    OrthographicCamera(
        float left, float right,
        float top, float bottom,
        float near, float far)
        : Camera((right - left) / (top - bottom)),
          left(left),
          right(right),
          top(top),
          bottom(bottom),
          near(near),
          far(far),
          dir({0, 0, far > near ? 1.0f : -1.0f}){};

    Ray generate_primary_ray(float x, float y) const override
    {
        Eigen::Vector3f origin{
            (right - left) * (1 + x) * 0.5f + left,
            (top - bottom) * (1 + y) * 0.5f + bottom,
            near};
        return Ray(origin, dir, std::abs(far - near));
    };

private:
    float left;
    float right;
    float top;
    float bottom;
    float near;
    float far;

    Eigen::Vector3f dir;
};

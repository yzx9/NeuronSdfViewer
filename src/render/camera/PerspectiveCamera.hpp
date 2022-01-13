#pragma once
#include "Camera.hpp"
#include "../Ray.hpp"

class PerspectiveCamera : public Camera
{
public:
    PerspectiveCamera(float fov, float aspect_radio, float near, float far) : Camera(aspect_radio), fov(fov), near(near), far(far){};

    Ray generate_primary_ray(float x, float y) const override
    {
        auto dir = Eigen::Vector3f{1.0f, 1.0f, 1.0f}.normalized();
        return Ray(dir, position);
    };

protected:
    float fov;
    float near;
    float far;
};

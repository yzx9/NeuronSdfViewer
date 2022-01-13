#pragma once
#include <limits>
#include <Eigen/Dense>

class Ray
{
private:
    Eigen::Vector3f origin;

    Eigen::Vector3f direction;

    float tMax;

public:
    Ray(Eigen::Vector3f origin, Eigen::Vector3f direction) : Ray(origin, direction, std::numeric_limits<float>::infinity()){};

    Ray(Eigen::Vector3f origin, Eigen::Vector3f direction, float max) : origin(origin), direction(direction), tMax(max){};

    Eigen::Vector3f operator()(float t) const { return origin + direction * t; };

    const Eigen::Vector3f &get_origin() const { return origin; };

    const Eigen::Vector3f &get_direction() const { return direction; };

    bool is_valid() const { return tMax == std::numeric_limits<float>::infinity() || tMax > 0; };

    bool is_valid(float t) const { return tMax == std::numeric_limits<float>::infinity() || tMax - t > std::numeric_limits<float>::epsilon(); };

    void set_t_max(float t_max) { this->tMax = t_max; };
};

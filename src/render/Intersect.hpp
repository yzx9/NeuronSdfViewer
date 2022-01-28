#pragma once
#include <Eigen/Dense>
#include <limits>

constexpr auto infinity = std::numeric_limits<float>::infinity();

class Intersect
{
public:
    Intersect() : happend(false), t(infinity){};

    Intersect(float t) : happend(true), t(t){};

    Intersect(float t, Eigen::Vector3f color) : Intersect(t) { this->color = color; };

    bool happend;

    float t;

    Eigen::Vector3f color;
};

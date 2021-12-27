#pragma once

#include <Eigen/Dense>

class Ray
{
public:
    Ray(Eigen::Vector3f origin, Eigen::Vector3f direction) : origin(origin), direction(direction){};
    Eigen::Vector3f operator()(float t) const;

private:
    Eigen::Vector3f origin;
    Eigen::Vector3f direction;
};

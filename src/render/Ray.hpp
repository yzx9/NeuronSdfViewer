#pragma once
#include <Eigen/Dense>

class Ray
{
public:
    Ray(Eigen::Vector3f origin, Eigen::Vector3f direction);
    Ray(Eigen::Vector3f origin, Eigen::Vector3f direction, float max);
    Eigen::Vector3f operator()(float t) const;
    void set_t_max(float t_max);
    bool is_valid();
    bool is_valid(float t);

private:
    Eigen::Vector3f origin;
    Eigen::Vector3f direction;
    float tMax;
};

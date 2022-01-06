#pragma once
#include <Eigen/Dense>

class Ray
{
public:
    Ray(Eigen::Vector3f origin, Eigen::Vector3f direction);

    Ray(Eigen::Vector3f origin, Eigen::Vector3f direction, float max);

    Eigen::Vector3f operator()(float t) const;

    const Eigen::Vector3f& get_origin() const;

    const Eigen::Vector3f& get_direction() const;

    bool is_valid() const;

    bool is_valid(float t) const;

    void set_t_max(float t_max);

private:
    Eigen::Vector3f origin;

    Eigen::Vector3f direction;
    
    float tMax;
};

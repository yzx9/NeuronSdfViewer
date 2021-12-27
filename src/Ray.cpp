#include "Ray.hpp"

Eigen::Vector3f Ray::operator()(float t) const
{
    return origin + direction * t;
}

#include <limits>
#include "SdfObject.hpp"
#include "../Intersect.hpp"

constexpr auto max_try_matching = 256;

SdfObject::SdfObject(Eigen::Vector3f position) : Object(position) {};

Intersect SdfObject::intersect_ray(const Ray& ray) const {
    constexpr auto infinity = std::numeric_limits<float>::infinity();
    return intersect_ray(ray, 0.0f, infinity);
}

// Ray Matching Algorithm
Intersect SdfObject::intersect_ray(const Ray& ray, const float& tMin, const float& tMax) const
{
    auto t = tMin;
    for (int i = 0; i < max_try_matching && ray.is_valid(t) && t < tMax; i++) {
        auto dis = sdf(ray(t));
        if (dis < std::numeric_limits<float>::epsilon())
            return Intersect(t);

        t += dis;
    }

    return Intersect();
}

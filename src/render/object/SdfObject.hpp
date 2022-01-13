#pragma once
#include <limits>
#include <Eigen/Dense>
#include "Object.hpp"
#include "../Intersect.hpp"
#include "../Ray.hpp"

class SdfObject : public Object
{
public:
    SdfObject(Eigen::Vector3f position) : Object(position){};

    Intersect intersect_ray(const Ray &ray) const override
    {
        constexpr auto infinity = std::numeric_limits<float>::infinity();
        return intersect_ray(ray, 0.0f, infinity);
    };

    // Ray Matching Algorithm
    Intersect intersect_ray(const Ray &ray, const float &tMin, const float &tMax) const override
    {
        constexpr auto max_try_matching = 256;

        auto t = tMin;
        for (int i = 0; i < max_try_matching && ray.is_valid(t) && t < tMax; i++)
        {
            auto dis = sdf(ray(t));
            if (dis < std::numeric_limits<float>::epsilon())
                return Intersect(t);

            t += dis;
        }

        return Intersect();
    };

    virtual float sdf(const Eigen::Vector3f &position) const = 0;
};

#pragma once
#include "../Ray.hpp"
#include "../accelerate/Bound3.hpp"

class Object
{
public:
    Object(Eigen::Vector3f position) : position(position) {};

    virtual bool intersect_ray(const Ray &ray) const = 0;

    virtual bool intersect_ray(const Ray& ray, const float& tMin, const float& tMax) const = 0;

    virtual Bound3 get_bound3() const = 0;

protected:
    Eigen::Vector3f position;
};

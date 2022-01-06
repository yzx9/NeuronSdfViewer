#pragma once
#include <memory>
#include "../Intersect.hpp"
#include "../Ray.hpp"
#include "../accelerate/Bound3.hpp"

class Object
{
public:
    Object(Eigen::Vector3f position) : position(position){};

    virtual Intersect intersect_ray(const Ray &ray) const = 0;

    virtual Intersect intersect_ray(const Ray &ray, const float &tMin, const float &tMax) const = 0;

    virtual std::unique_ptr<Bound3> build_bound3() const = 0;

protected:
    Eigen::Vector3f position;
};

module;
#include <memory>
#include <Eigen/Dense>
export module Render.Basis:Object;

import :Intersect;
import Render.Accelerate;

export class Object
{
public:
    Object(Eigen::Vector3f position) : position(position){};

    virtual ~Object() {};

    virtual Intersect intersect_ray(const Ray &ray) const = 0;

    virtual Intersect intersect_ray(const Ray &ray, const float &tMin, const float &tMax) const = 0;

    virtual std::unique_ptr<Bound3> build_bound3() const = 0;

protected:
    Eigen::Vector3f position;
};

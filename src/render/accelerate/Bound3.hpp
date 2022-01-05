#pragma once
#include <memory>
#include <Eigen/Dense>
#include "Bound3Intersect.hpp"
#include "../Ray.hpp"

class Bound3
{
public:
    Bound3(Eigen::Vector3f min, Eigen::Vector3f max);

    Bound3Intersect intersect_ray(const Ray &ray) const;

    static std::unique_ptr<Bound3> union_bound3(const std::unique_ptr<Bound3> &box1, const std::unique_ptr<Bound3> &box2);

    const Eigen::Vector3f& min();

    const Eigen::Vector3f& max();

private:
    Eigen::Vector3f _min;

    Eigen::Vector3f _max;
};

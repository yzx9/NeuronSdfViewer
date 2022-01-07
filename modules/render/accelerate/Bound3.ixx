module;
#include <memory>
#include <Eigen/Dense>
export module Render.Accelerate:Bound3;

import :Bound3Intersect;
import Render.Basis;

export class Bound3
{
public:
    Bound3(Eigen::Vector3f min, Eigen::Vector3f max) : _min(min), _max(max) {};

    Bound3Intersect intersect_ray(const Ray &ray) const
    {
        const auto& origin = ray.get_origin();
        const auto& dir = ray.get_direction();

        auto tIn = (_min - origin).cwiseQuotient(dir).minCoeff();
        auto tOut = (_max - origin).cwiseQuotient(dir).maxCoeff();

        if (tIn < std::numeric_limits<float>::epsilon())
            return Bound3Intersect(0.0f, tOut);

        if (tOut - tIn > -std::numeric_limits<float>::epsilon())
            return Bound3Intersect(tIn, tOut);

        return Bound3Intersect();
    };

    static std::unique_ptr<Bound3> union_bound3(const std::unique_ptr<Bound3> &box1, const std::unique_ptr<Bound3> &box2)
    {
        auto min = box1->_min.cwiseMin(box2->_min);
        auto max = box1->_max.cwiseMax(box2->_max);
        return std::make_unique<Bound3>(min, max);
    };

    const Eigen::Vector3f& min() { return _min; };

    const Eigen::Vector3f& max() { return _max; };

private:
    Eigen::Vector3f _min;

    Eigen::Vector3f _max;
};

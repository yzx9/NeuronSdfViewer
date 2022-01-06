#include <math.h>
#include <memory>
#include <limits>
#include <Eigen/Dense>
#include "Bound3.hpp"
#include "Bound3Intersect.hpp"
#include "../Ray.hpp"

Bound3::Bound3(Eigen::Vector3f min, Eigen::Vector3f max)
    : _min(min), _max(max)
{
}

Bound3Intersect Bound3::intersect_ray(const Ray &ray) const
{
    const auto &origin = ray.get_origin();
    const auto &dir = ray.get_direction();

    auto tIn = std::max({
        (_min.x() - origin.x()) / dir.x(),
        (_min.y() - origin.y()) / dir.y(),
        (_min.z() - origin.z()) / dir.z(),
        });

    auto tOut = std::min({
        (_max.x() - origin.x()) / dir.x(),
        (_max.y() - origin.y()) / dir.y(),
        (_max.z() - origin.z()) / dir.z(),
        });

    if (tIn < std::numeric_limits<float>::epsilon())
        return Bound3Intersect(0.0f, tOut);

    if (tOut - tIn > -std::numeric_limits<float>::epsilon())
        return Bound3Intersect(tIn, tOut);

    return Bound3Intersect();
}

std::unique_ptr<Bound3> Bound3::union_bound3(const std::unique_ptr<Bound3> &box1, const std::unique_ptr<Bound3> &box2)
{
    return std::make_unique<Bound3>(
        Eigen::Vector3f{
            std::min(box1->_min.x(), box2->_min.x()),
            std::min(box1->_min.y(), box2->_min.y()),
            std::min(box1->_min.z(), box2->_min.z()),
        },
        Eigen::Vector3f{
            std::max(box1->_max.x(), box2->_max.x()),
            std::max(box1->_max.y(), box2->_max.y()),
            std::max(box1->_max.z(), box2->_max.z()),
        });
}

const Eigen::Vector3f& Bound3::min() { return _min; }

const Eigen::Vector3f& Bound3::max() { return _max; }

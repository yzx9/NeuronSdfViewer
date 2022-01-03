#include <math.h>
#include <memory>
#include <limits>
#include <Eigen/Dense>
#include "Bound3.hpp"
#include "Bound3Intersect.hpp"
#include "../Ray.hpp"

Bound3::Bound3(Eigen::Vector3f min, Eigen::Vector3f max)
    : min(min), max(max)
{
}

Bound3Intersect Bound3::intersect_ray(const Ray &ray) const
{
    const auto &origin = ray.get_origin();
    const auto &dir = ray.get_direction();

    auto tIn = std::max({
        (min.x() - origin.x()) / dir.x(),
        (min.y() - origin.y()) / dir.y(),
        (min.z() - origin.z()) / dir.z(),
    });

    auto tOut = std::min({
        (max.x() - origin.x()) / dir.x(),
        (max.y() - origin.y()) / dir.y(),
        (max.z() - origin.z()) / dir.z(),
    });

    return tOut - tIn > -std::numeric_limits<float>::epsilon()
               ? Bound3Intersect(tIn, tOut)
               : Bound3Intersect();
}

std::unique_ptr<Bound3> Bound3::union_bound3(const std::unique_ptr<Bound3> &box1, const std::unique_ptr<Bound3> &box2)
{
    auto bound3 = Bound3(
        {
            std::min(box1->min.x(), box2->min.x()),
            std::min(box1->min.y(), box2->min.y()),
            std::min(box1->min.z(), box2->min.z()),
        },
        {
            std::max(box1->max.x(), box2->max.x()),
            std::max(box1->max.y(), box2->max.y()),
            std::max(box1->max.z(), box2->max.z()),
        });
    return std::make_unique<Bound3>(bound3);
}

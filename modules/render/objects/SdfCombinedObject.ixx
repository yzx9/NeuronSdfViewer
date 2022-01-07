module;
#include <vector>
#include <memory>
#include <limits>
#include <math.h>
#include <Eigen/Dense>
export module Render.Object.Sdf:CombinedObject;

import :Object;
import Render.Accelerate;

export class SdfCombinedObject : public SdfObject
{
public:
    float sdf(const Eigen::Vector3f &position) const;

    void add(std::unique_ptr<SdfObject> object);

    std::unique_ptr<Bound3> build_bound3() const override;

protected:
    std::vector<std::unique_ptr<SdfObject>> objects;
};

float SdfCombinedObject::sdf(const Eigen::Vector3f& position) const
{
    auto min = std::numeric_limits<float>::max();
    for (auto& object : objects)
    {
        // TOOD: support mix function
        if (auto sdf = object->sdf(position); sdf < min)
            min = sdf;
    }

    return min;
}

void SdfCombinedObject::add(std::unique_ptr<SdfObject> object)
{
    objects.emplace_back(std::move(object));
}

std::unique_ptr<Bound3> SdfCombinedObject::build_bound3() const
{
    const auto size = objects.size();
    if (size == 0)
        throw std::runtime_error("Build bound3 before add any object");

    if (size == 1)
        return objects[0]->build_bound3();

    auto bound3 = objects[0]->build_bound3();
    for (int i = 1; i < size; i++)
    {
        bound3 = Bound3::union_bound3(bound3, objects[i]->build_bound3());
    }
    return bound3;
}


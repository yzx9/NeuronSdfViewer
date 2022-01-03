#pragma once
#include <vector>
#include <memory>
#include <Eigen/Dense>
#include "SdfObject.hpp"
#include "SdfCombinedObject.hpp"
#include "../accelerate/Bound3.hpp"

class SdfCombinedObject : public SdfObject
{
public:
    float sdf(const Eigen::Vector3f &position) const;

    void add(std::unique_ptr<SdfObject> object);

    std::unique_ptr<Bound3> build_bound3() const override;

protected:
    std::vector<std::unique_ptr<SdfObject>> objects;
};

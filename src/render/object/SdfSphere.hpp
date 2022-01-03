#pragma once
#include <memory>
#include <Eigen/Dense>
#include "SdfObject.hpp"
#include "../Ray.hpp"
#include "../accelerate/Bound3.hpp"

class SdfSphere : public SdfObject
{
public:
    SdfSphere(Eigen::Vector3f position, float radis);

    float sdf(const Eigen::Vector3f &position) const override;

    std::unique_ptr<Bound3> build_bound3() const override;

private:
    float radis;
};

#pragma once
#include <memory>
#include <Eigen/Dense>
#include "SdfObject.hpp"
#include "../Ray.hpp"
#include "../accelerate/Bound3.hpp"

class SdfSphere : public SdfObject
{
public:
    SdfSphere(Eigen::Vector3f position, float radis) : SdfObject(position), radis(radis){};

    float sdf(const Eigen::Vector3f &position) const override
    {
        return (position - this->position).norm() - radis;
    };

    std::unique_ptr<Bound3> build_bound3() const override
    {
        auto min = position - Eigen::Vector3f::Ones(radis);
        auto max = position + Eigen::Vector3f::Ones(radis);
        return std::make_unique<Bound3>(min, max);
    };

private:
    float radis;
};

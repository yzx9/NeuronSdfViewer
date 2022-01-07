module;
#include <memory>
#include <Eigen/Dense>
export module Render.Object.Sdf:Sphere;

import :Object;
import Render.Accelerate;

export class SdfSphere : public SdfObject
{
public:
    SdfSphere(Eigen::Vector3f position, float radis) : SdfObject(center), radis(radis) {};

    float sdf(const Eigen::Vector3f &position) const override
    {
        return (position - this->position).norm() - radis;
    };

    std::unique_ptr<Bound3> build_bound3() const override
    {
        Eigen::Vector3f min{
            position.x() - radis,
            position.y() - radis,
            position.z() - radis,
        };
        Eigen::Vector3f max{
            position.x() + radis,
            position.y() + radis,
            position.z() + radis,
        };
        return std::make_unique<Bound3>(min, max);
    };

private:
    float radis;
};

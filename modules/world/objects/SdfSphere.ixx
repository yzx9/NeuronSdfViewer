module;
#include <memory>
#include <Eigen/Dense>
export module World.Objects.Sdf.Sphere;

import Render.Accelerate.Bound3;
import World.Objects.Sdf.Object;

export class SdfSphere : public SdfObject
{
public:
    SdfSphere(Eigen::Vector3f position, float radis);

    float sdf(const Eigen::Vector3f &position) const override;

    std::unique_ptr<Bound3> build_bound3() const override;

private:
    float radis;
};

SdfSphere::SdfSphere(Eigen::Vector3f center, float radis)
    : SdfObject(center), radis(radis)
{
}

float SdfSphere::sdf(const Eigen::Vector3f& position) const
{
    return (position - this->position).norm() - radis;
}

std::unique_ptr<Bound3> SdfSphere::build_bound3() const
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
}


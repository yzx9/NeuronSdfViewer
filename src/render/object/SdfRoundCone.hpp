#include <Eigen/Dense>
#include "SdfObject.hpp"
#include "../accelerate/Bound3.hpp"

class SdfRoundCone : public SdfObject
{
public:
    SdfRoundCone(Eigen::Vector3f a, Eigen::Vector3f b, float ra, float rb);

    float sdf(const Eigen::Vector3f &position) const override;

    Bound3 get_bound3() const override;

private:
    Eigen::Vector3f a;
    Eigen::Vector3f b;
    float ra;
    float rb;
};

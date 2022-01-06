#include <math.h>
#include <memory>
#include <Eigen/Dense>
#include "SdfRoundCone.hpp"
#include "../accelerate/Bound3.hpp"

using Eigen::Vector3f;

SdfRoundCone::SdfRoundCone(Vector3f a, Vector3f b, float ra, float rb)
    : SdfObject(a), a(a), b(b), ra(ra), rb(rb)
{
}

inline int sign(auto a)
{
    return a >= 0 ? 1 : -1;
}

inline auto dot(Vector3f a)
{
    return a.dot(a);
}

float SdfRoundCone::sdf(const Vector3f &p) const
{
    // sampling independent computations (only depend on shape)
    auto ba = b - a;
    auto l2 = dot(ba);
    auto rr = ra - rb;
    auto a2 = l2 - rr * rr;
    auto il2 = 1.0f / l2;

    // sampling dependant computations
    auto pa = p - a;
    auto y = pa.dot(ba);
    auto z = y - l2;
    auto x2 = dot(pa * l2 - ba * y);
    auto y2 = y * y * l2;
    auto z2 = z * z * l2;

    // single square root!
    auto k = sign(rr) * rr * rr * x2;
    if (sign(z) * a2 * z2 > k)
        return sqrt(x2 + z2) * il2 - rb;
    if (sign(y) * a2 * y2 < k)
        return sqrt(x2 + y2) * il2 - ra;
    return (sqrt(x2 * a2 * il2) + y * rr) * il2 - ra;
}

std::unique_ptr<Bound3> SdfRoundCone::build_bound3() const
{
    Vector3f min{
        std::min(a.x() - ra, b.x() - rb),
        std::min(a.y() - ra, b.y() - rb),
        std::min(a.z() - ra, b.z() - rb),
    };
    Vector3f max{
        std::max(a.x() + ra, b.x() + rb),
        std::max(a.y() + ra, b.y() + rb),
        std::max(a.z() + ra, b.z() + rb),
    };
    auto bound3 = std::make_unique<Bound3>(min, max);
    return std::move(bound3);
}

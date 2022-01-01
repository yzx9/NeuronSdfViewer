#include "SdfSphere.hpp"
#include "../accelerate/Bound3.hpp"

SdfSphere::SdfSphere(Eigen::Vector3f center, float radis)
	: SdfObject(center), radis(radis)
{
}

float SdfSphere::sdf(const Eigen::Vector3f& position) const
{
	return (position - this->position).norm() - radis;
}

Bound3 SdfSphere::get_bound3() const
{
	return Bound3(
		{ position.x() - radis, position.y() - radis, position.z() - radis },
		{ position.x() + radis, position.y() + radis, position.z() + radis });
}

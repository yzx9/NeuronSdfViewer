#include "SdfSphere.hpp"

SdfSphere::SdfSphere(Eigen::Vector3f center, float radis)
	: SdfObject(center), radis(radis)
{
}

float SdfSphere::sdf(const Eigen::Vector3f& position) const
{
	return (position - this->position).norm() - radis;
}
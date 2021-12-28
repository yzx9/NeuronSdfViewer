#include "SdfSphere.hpp"

SdfSphere::SdfSphere(Eigen::Vector3f&& center, float radis)
	: center(center), radis(radis)
{
}

float SdfSphere::sdf(const Eigen::Vector3f& position) const
{
	return (position - center).norm() - radis;
}

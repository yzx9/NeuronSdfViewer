#include "SdfSphere.hpp"

SdfSphere::SdfSphere(Eigen::Vector3f center, float radis)
	: center(center), radis(radis)
{
}

SdfSphere::SdfSphere(Eigen::Vector3f&& center, float radis)
	: center(center), radis(radis)
{
}

bool SdfSphere::intesect_ray(Ray& ray) const {
	return false;
}

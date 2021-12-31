#include <Eigen/Dense>
#include "PerspectiveCamera.hpp"

PerspectiveCamera::PerspectiveCamera(float fov, float aspect_radio, float near, float far)
	: Camera(aspect_radio), fov(fov), near(near), far(far)
{
}

Ray PerspectiveCamera::generate_primary_ray(float x, float y) const
{
	auto dir = Eigen::Vector3f { 1.0f, 1.0f, 1.0f }.normalized();
	return Ray(dir, position);
}

#include "PerspectiveCamera.hpp"

PerspectiveCamera::PerspectiveCamera(float fov, float aspect_radio, float near, float far)
	: Camera(aspect_radio), fov(fov)
{
}

Ray PerspectiveCamera::generate_primary_ray(float x, float y)
{
	auto dir = Eigen3::Vector3f {

	}.normalized();
	return Ray(ray, position);
}

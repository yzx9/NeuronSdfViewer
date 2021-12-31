#include <math.h>
#include "OrthographicCamera.hpp"

OrthographicCamera::OrthographicCamera(float left, float right, float top, float bottom, float near, float far)
	: left(left), right(right), top(top), bottom(bottom), near(near), far(far),
	Camera((right - left) / (top - bottom))
{
}

Ray OrthographicCamera::generate_primary_ray(float x, float y) const
{
	Eigen::Vector3f origin{
		(right - left) * (1 + x) * 0.5f + left,
		(top - bottom) * (1 + y) * 0.5f + bottom,
		near
	};
	auto dir = (far - near) > 0 ? 1.0f : -1.0f;
	return Ray(origin, { 0, 0, dir });
}

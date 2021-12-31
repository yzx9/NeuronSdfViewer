#include "OrthographicCamera.hpp"

OrthographicCamera::OrthographicCamera(float left, float right, float top, float bottom, float near, float far)
	: left(left), right(right), top(top), bottom(bottom), near(near), far(far),
	Camera((right - left) / (top - bottom))
{
}

Ray OrthographicCamera::generate_primary_ray(float x, float y) const
{
	return Ray({ x, y, -1 }, { 0, 0, 1 });
}

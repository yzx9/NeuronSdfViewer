module;
#include <math.h>
export module Render.Cameras.OrthographicCamera;

import Render.Ray;
import Render.Cameras.Camera;

export class OrthographicCamera : public Camera {
public:
	OrthographicCamera(
		float left,
		float right,
		float top,
		float bottom,
		float near,
		float far);

	Ray generate_primary_ray(float x, float y) const override;

private:
	float left;
	float right;
	float top;
	float bottom;
	float near; 
	float far;
};

OrthographicCamera::OrthographicCamera(float left, float right, float top, float bottom, float near, float far)
	: Camera((right - left) / (top - bottom)),
	left(left), right(right), top(top), bottom(bottom), near(near), far(far)
{
}

Ray OrthographicCamera::generate_primary_ray(float x, float y) const
{
	Eigen::Vector3f origin{
		(right - left) * (1 + x) * 0.5f + left,
		(top - bottom) * (1 + y) * 0.5f + bottom,
		near };
	auto sign = far > near ? 1.0f : -1.0f;
	return Ray(origin, { 0, 0, sign }, std::abs(far - near));
}


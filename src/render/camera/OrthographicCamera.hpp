#pragma once
#include "Camera.hpp"
#include "../Ray.hpp"

class OrthographicCamera : public Camera {
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

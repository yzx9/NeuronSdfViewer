#pragma once
#include "Camera.hpp"
#include "../Ray.hpp"

class PerspectiveCamera : public Camera {
public:
	PerspectiveCamera(float fov, float aspect_radio, float near, float far);

	Ray generate_primary_ray(float x, float y) const override;

protected:
	float fov;
	float near;
	float far;
};
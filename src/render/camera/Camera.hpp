#pragma once

#include "../Ray.hpp"

class Camera
{
public:
	Camera(float aspect_radio) : aspect_radio(aspect_radio) {}
	virtual Ray generate_primary_ray(float x, float y) const = 0;

protected:
	double aspect_radio;
};
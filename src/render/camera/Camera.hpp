#pragma once
#include <Eigen/Dense>
#include "../Ray.hpp"

class Camera
{
public:
	Camera(float aspect_radio);

	Camera(Eigen::Vector3f position, float aspect_radio);
	
	virtual Ray generate_primary_ray(float x, float y) const = 0;

protected:
	Eigen::Vector3f position;

	double aspect_radio;
};
module;
#include <Eigen/Dense>
export module Render.Cameras.Camera;

import Render.Ray;

export class Camera
{
public:
	Camera(float aspect_radio);

	Camera(Eigen::Vector3f position, float aspect_radio);

	virtual ~Camera() {};
	
	virtual Ray generate_primary_ray(float x, float y) const = 0;

protected:
	Eigen::Vector3f position;

	double aspect_radio;
};

Camera::Camera(float aspect_radio)
	: Camera({ 0.0f, 0.0f, 0.0f }, aspect_radio)
{
}

Camera::Camera(Eigen::Vector3f position, float aspect_radio)
	: position(position), aspect_radio(aspect_radio)
{
}

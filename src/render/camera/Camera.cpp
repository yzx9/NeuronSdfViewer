#include "Camera.hpp"

Camera::Camera(float aspect_radio)
	: Camera({ 0.0f, 0.0f, 0.0f }, aspect_radio)
{
}

Camera::Camera(Eigen::Vector3f position, float aspect_radio)
	: position(position), aspect_radio(aspect_radio)
{
}

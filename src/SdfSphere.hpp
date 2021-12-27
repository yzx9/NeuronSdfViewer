#include <Eigen/Dense>
#include "Object.hpp"

class SdfSphere : Object {
public:
	SdfSphere(Eigen::Vector3f center, float radis);
	SdfSphere(Eigen::Vector3f&& center, float radis);

	bool Object::intesect_ray(Ray& ray) const override;

private:
	Eigen::Vector3f center;
	float radis;
};
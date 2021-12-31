#pragma once

#include <Eigen/Dense>
#include "Object.hpp"
#include "../Ray.hpp"

class SdfObject : public Object {
public:
	SdfObject(Eigen::Vector3f position);

	bool intesect_ray(Ray& ray) const override;

	virtual float sdf(const Eigen::Vector3f& position) const = 0;
};
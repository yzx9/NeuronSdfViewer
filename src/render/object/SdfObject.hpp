#pragma once
#include <Eigen/Dense>
#include "Object.hpp"
#include "../Intersect.hpp"
#include "../Ray.hpp"

class SdfObject : public Object {
public:
	SdfObject(Eigen::Vector3f position);

	Intersect intersect_ray(const Ray& ray) const override;

	Intersect intersect_ray(const Ray& ray, const float& tMin, const float& tMax) const override;

	virtual float sdf(const Eigen::Vector3f& position) const = 0;
};
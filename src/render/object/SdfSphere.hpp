#pragma once

#include <Eigen/Dense>
#include "SdfObject.hpp"
#include "../Ray.hpp"

class SdfSphere : public SdfObject {
public:
	SdfSphere(Eigen::Vector3f position, float radis) : SdfObject(position);

	float sdf(const Eigen::Vector3f& position) const override;

private:
	float radis;
};
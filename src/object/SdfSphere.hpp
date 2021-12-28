#pragma once

#include <Eigen/Dense>
#include "SdfObject.hpp"
#include "../Ray.hpp"

class SdfSphere : public SdfObject {
public:
	SdfSphere(Eigen::Vector3f&& center, float radis);

	float sdf(const Eigen::Vector3f& position) const override;

private:
	Eigen::Vector3f center;
	float radis;
};
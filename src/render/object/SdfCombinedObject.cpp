#include <vector>
#include <memory>
#include <math.h>
#include <limits>
#include <Eigen/Dense>
#include "SdfCombinedObject.hpp"

float SdfCombinedObject::sdf(const Eigen::Vector3f& position) const
{
	auto min = std::numeric_limits<float>::max();
	for (auto& object : objects) {
		if (auto sdf = object->sdf(position); sdf < min) {
			min = sdf;
		}
	}

	return min;
}

void SdfCombinedObject::add(std::unique_ptr<SdfObject> object)
{
	objects.emplace_back(std::move(object));
}

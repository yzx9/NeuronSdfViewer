#pragma once
#include <vector>
#include <memory>
#include <Eigen/Dense>
#include "SdfCombinedObject.hpp"

class SdfCombinedObject : SdfObject
{
public:
	float sdf(const Eigen::Vector3f& position) const;

	void add(std::unique_ptr<SdfObject> object);

protected:
	std::vector<std::unique_ptr<SdfObject>> objects;
};

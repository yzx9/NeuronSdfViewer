#include <Eigen/Dense>
#include "SwcLoader.hpp"
#include "../render/object/SdfSphere.hpp"

using objects = std::vector<std::unique_ptr<SdfObject>>;

objects SwcLoader::load(const std::string& filepath)
{
	objects objs;
	objs.emplace_back(std::make_unique<SdfSphere>(Eigen::Vector3f(0, 0, 200.0f), 100.0f));
	return objs;
}

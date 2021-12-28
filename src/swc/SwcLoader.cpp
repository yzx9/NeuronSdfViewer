#include "SwcLoader.hpp"
#include "../object/SdfSphere.hpp"

using objects = std::vector<std::unique_ptr<SdfObject>>;

objects SwcLoader::load(std::string filepath)
{
	auto sphere = std::make_unique<SdfSphere>(Eigen::Vector3f{ 0, 0, 0 }, 0.5f);
	return { std::move(sphere) };
}

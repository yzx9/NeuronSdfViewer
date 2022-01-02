#include <string>
#include <memory>
#include "NeuronScene.hpp"
#include "SwcLoader.hpp"
#include "SwcNode.hpp"
#include "../render/object/SdfSphere.hpp"

void NeuronScene::load(std::string filepath)
{
	auto root = SwcLoader::load(filepath);
	addSwcTree(root);
}

void NeuronScene::addSwcTree(const std::shared_ptr<SwcNode>& root)
{
	if (!root) return;

	auto sphere = std::make_unique<SdfSphere>(Eigen::Vector3f(root->x, root->y, root->z), root->raidus);
	add(std::move(sphere));

	if (root->child) addSwcTree(root->child);

	if (root->next) addSwcTree(root->next);
}

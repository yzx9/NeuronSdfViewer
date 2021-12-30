#include <string>
#include "NeuronScene.hpp"
#include "SwcLoader.hpp"

void NeuronScene::load(std::string filepath)
{
	auto nodes = SwcLoader::load(filepath);
	for (auto& node : nodes) {
		add(std::move(node));
	}
}
 
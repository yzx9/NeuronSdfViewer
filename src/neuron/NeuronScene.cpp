#include <string>
#include "NeuronScene.hpp"
#include "SwcLoader.hpp"

NeuronScene::NeuronScene(int width, int height) : Scene(width, height)
{

}

NeuronScene::~NeuronScene()
{
}

void NeuronScene::load(std::string filepath)
{
	auto nodes = SwcLoader::load(filepath);
	for (auto& node : nodes) {
		add(std::move(node));
	}
}
 
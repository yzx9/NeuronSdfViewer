#pragma once
#include "SwcNode.hpp"
#include "../render/Scene.hpp"

class NeuronScene : public Scene
{
public:
	void load(std::string filepath);

private:
	void addSwcTree(const std::shared_ptr<SwcNode>& root);
};

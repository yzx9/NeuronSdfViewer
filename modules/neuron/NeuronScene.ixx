module;
#include <memory>
#include <string>
export module Neuron.Scene;

import Neuron.SwcNode;
import Render.Scene;

export class NeuronScene : public Scene
{
public:
    void load(std::string filepath);

private:
    void addSwcTree(const std::unique_ptr<SwcNode>& root, const std::unique_ptr<SwcNode>& parent);
};

module;
#include <memory>
#include <string>
#include <Eigen/Dense>
export module Neuron:Scene;

import :SwcLoader;
import :SwcNode;
import Render;

export class NeuronScene : public Scene
{
public:
    void load(std::string filepath);

private:
    void addSwcTree(std::unique_ptr<SwcNode> const&root, std::unique_ptr<SwcNode> const&parent)
    {
        if (parent)
        {
            auto roundCone = std::make_unique<SdfRoundCone>(
                Eigen::Vector3f(root->x, root->y, root->z),
                Eigen::Vector3f(parent->x, parent->y, parent->z),
                root->raidus,
                parent->raidus);
            add(std::move(roundCone));
        }
        else if (!root->child)
        {
            auto sphere = std::make_unique<SdfSphere>(Eigen::Vector3f(root->x, root->y, root->z), root->raidus);
            add(std::move(sphere));
        }

        if (root->next)
            addSwcTree(root->next, parent);

        if (root->child)
            addSwcTree(root->child, root);
    };
};

void NeuronScene::load(std::string filepath)
{
    auto root = SwcLoader::load(filepath);

    if (!root)
        return;

    addSwcTree(root, nullptr);
}

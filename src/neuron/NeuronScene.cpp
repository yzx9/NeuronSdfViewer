#include <string>
#include <memory>
#include <Eigen/Dense>
#include "NeuronScene.hpp"
#include "SwcLoader.hpp"
#include "SwcNode.hpp"
#include "../render/object/SdfSphere.hpp"
#include "../render/object/SdfRoundCone.hpp"

void NeuronScene::load(std::string filepath)
{
    auto root = SwcLoader::load(filepath);

    if (!root)
        return;

    addSwcTree(root, nullptr);
}

void NeuronScene::addSwcTree(const std::unique_ptr<SwcNode> &root, const std::unique_ptr<SwcNode> &parent)
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
}

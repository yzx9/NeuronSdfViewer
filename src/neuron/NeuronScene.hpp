#pragma once
#include <string>
#include <memory>
#include <unordered_map>
#include <Eigen/Dense>
#include "NeuronScene.hpp"
#include "SwcLoader.hpp"
#include "SwcNode.hpp"
#include "../render/Scene.hpp"
#include "../render/object/SdfSphere.hpp"
#include "../render/object/SdfRoundCone.hpp"
#include "../render/material/Material.hpp"
#include "../render/material/MaterialDiffuse.hpp"

class NeuronScene : public Scene
{
public:
    void load(std::string filepath)
    {
        auto root = SwcLoader::load(filepath);
        if (!root)
            return;

        add_swc_tree(root, nullptr);
    };

private:
    std::unordered_map<std::string, std::shared_ptr<Material>> materials
    {
        {"White",   std::make_unique<MaterialDiffuse>(Eigen::Vector3f{ 0.0, 0.0, 0.0 })},
        {"Red",     std::make_unique<MaterialDiffuse>(Eigen::Vector3f{ 1.0, 0.0, 0.0 })},
        {"Green",   std::make_unique<MaterialDiffuse>(Eigen::Vector3f{ 0.0, 1.0, 0.0 })},
        {"Blue",    std::make_unique<MaterialDiffuse>(Eigen::Vector3f{ 0.0, 0.0, 1.0 })}
    };

    void add_swc_tree(const std::unique_ptr<SwcNode> &root, const std::unique_ptr<SwcNode> &parent)
    {
        if (parent)
            add(std::move(create_cone(root, parent)));
        else if (!root->child)
            add(std::move(create_root(root)));

        if (root->next)
            add_swc_tree(root->next, parent);

        if (root->child)
            add_swc_tree(root->child, root);
    };

    std::unique_ptr<Object> create_cone(const std::unique_ptr<SwcNode>& root, const std::unique_ptr<SwcNode>& parent)
    {
        auto roundCone = std::make_unique<SdfRoundCone>(
            Eigen::Vector3f(root->x, root->y, root->z),
            Eigen::Vector3f(parent->x, parent->y, parent->z),
            root->raidus,
            parent->raidus);
        roundCone->set_material(materials["Red"]);
        return roundCone;
    }

    std::unique_ptr<Object> create_root(const std::unique_ptr<SwcNode>& root)
    {
        auto sphere = std::make_unique<SdfSphere>(
            Eigen::Vector3f{ root->x, root->y, root->z },
            root->raidus);
        sphere->set_material(materials["Green"]);
        return sphere;
    }
};

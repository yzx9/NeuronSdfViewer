#include <exception>
#include <fstream>
#include <string>
#include <stdexcept>
#include <unordered_map>
#include <memory>
#include <Eigen/Dense>
#include "SwcLoader.hpp"
#include "SwcNode.hpp"

std::shared_ptr<SwcNode> SwcLoader::load(const std::string& filepath)
{
    std::ifstream file(filepath);
    if (!file.is_open())
    {
        throw std::runtime_error("Open SWC file failed!");
    }

    std::shared_ptr<SwcNode> root;
    std::unordered_map<int, std::shared_ptr<SwcNode>> map;
    std::string s;
    while (std::getline(file, s))
    {
        std::shared_ptr<SwcNode> node;
        if (s.starts_with('#') || !SwcNode::try_parse(s, node))
        {
            continue;
        }

        if (map.contains(node->id))
        {
            throw std::runtime_error("Invalid SWC file: duplicate id!");
        }

        map.insert(std::make_pair(node->id, std::move(node)));
    }
    file.close();

    root = nullptr;
    for (auto& [id, node]: map) {
        if (node->parent == -1) // TODO: 此处假设根节点一定为-1是否正确？
        {
            root = node;
        }

        if (map.contains(node->parent))
        {
            auto& parent = map.at(node->parent);
            if (parent->child)
            {
                std::shared_ptr child = parent->child;
                while (child->next) child = child->next;
                child->next = node;
            }
            else
            {
                parent->child = node;
            }
        }
    }

    if (root == nullptr)
    {
        throw std::runtime_error("Invalid SWC file: can't find root!");
    }

    return root;
}

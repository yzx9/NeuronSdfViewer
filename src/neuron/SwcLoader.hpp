#pragma once
#include <exception>
#include <fstream>
#include <functional>
#include <string>
#include <stdexcept>
#include <vector>
#include <map>
#include <memory>
#include <Eigen/Dense>
#include "SwcNode.hpp"

class SwcLoader
{
public:
    static std::unique_ptr<SwcNode> load(const std::string &filepath)
    {
        std::ifstream file(filepath);
        if (!file.is_open())
        {
            throw std::runtime_error("Open SWC file failed!");
        }

        std::unique_ptr<SwcNode> root;
        std::map<int, std::unique_ptr<SwcNode>> map;
        std::string s;
        while (std::getline(file, s))
        {
            std::unique_ptr<SwcNode> node;
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

        // TODO: 此处两个假设是否一定成立？
        //   - 根节点id=1
        //   - 节点id一定大于父节点id

        std::function<std::unique_ptr<SwcNode> &(std::unique_ptr<SwcNode> &)>
            getLastChild = [&](std::unique_ptr<SwcNode> &node) -> std::unique_ptr<SwcNode> &
        {
            if (node->next)
                return getLastChild(node->next);

            return node;
        };

        for (auto it = map.rbegin(); it != map.rend(); it++)
        {
            auto &node = it->second;
            if (map.contains(node->parent))
            {
                auto &parent = map.at(node->parent);
                if (parent->child)
                {
                    auto &child = getLastChild(parent->child);
                    child->next = std::move(node);
                }
                else
                {
                    parent->child = std::move(node);
                }
            }
        }

        if (!map.contains(1))
        {
            throw std::runtime_error("Invalid SWC file: can't find root!");
        }

        auto &node = map.at(1);
        return std::move(node);
    };
};

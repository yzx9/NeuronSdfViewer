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
            throw std::runtime_error("Open SWC file failed!");

        using pNode = std::unique_ptr<SwcNode>;
        std::map<int, pNode> map;
        std::string s;
        while (std::getline(file, s))
        {
            pNode node;
            if (s.starts_with('#') || !SwcNode::try_parse(s, node))
                continue;

            if (map.contains(node->id))
                throw std::runtime_error("Invalid SWC file: duplicate id!");

            map[node->id] = std::move(node);
        }
        file.close();

        // TODO: 此处两个假设是否一定成立？
        //   - 根节点id=1
        //   - 节点id一定大于父节点id
        for (auto it = map.rbegin(); it != map.rend(); it++)
            if (auto &node = it->second; map.contains(node->parent))
                map.at(node->parent)->add_child(std::move(node));

        if (!map.contains(1))
            throw std::runtime_error("Invalid SWC file: can't find root!");

        return std::move(map.at(1));
    };
};

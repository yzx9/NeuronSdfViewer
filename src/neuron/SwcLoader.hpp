#pragma once
#include <string>
#include <vector>
#include <memory>
#include "SwcNode.hpp"

class SwcLoader
{
public:
    static std::unique_ptr<SwcNode> load(const std::string &filepath);
};
